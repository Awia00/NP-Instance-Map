#pragma once
#include <map>
#include <mutex>
#include <np_solver/filters/instance_filter.hpp>
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/solvers/instance_solver.hpp>
#include <set>

namespace npim
{
template <class SpecificGraph>
class IsomorphicGraphPermutationRunner
{
    protected:
    std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> filters;
    std::vector<std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> solvers;

    public:
    IsomorphicGraphPermutationRunner(
        const std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>>& filters,
                      const std::vector<std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>>& solvers)
      : filters(filters), solvers(solvers)
    {
    }

	/**
	* Runs the solvers on each fundemental graph up to size V determined by template SpecificGraph.
	**/
	void solve_all() const
    {
        constexpr uint64_t V = SpecificGraph::vertices();
        constexpr uint64_t number_of_graphs = SpecificGraph::number_of_graphs();
        std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;

        auto stats = std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>();
        auto all_graphs = std::vector<uint64_t>();
        all_graphs.reserve(factorial<V>()); // a bit too much, but this was the closest asymptotics I could find.

        auto all_graphs_mutex = std::mutex();
        auto stats_mutex = std::mutex();

        filter_and_solve_graph(SpecificGraph(0), stats, all_graphs, all_graphs_mutex, stats_mutex); // add initial graph with 1 vertex, 0 edges.
        for (uint64_t specific_v = 2; specific_v <= V; specific_v++)
        {
            std::cout << "V: " << specific_v << std::endl;
            solve_specific_v(specific_v, stats, all_graphs, all_graphs_mutex, stats_mutex);
            std::cout << all_graphs.size() << std::endl;
        }
        std::cout << std::endl;
        print_stats(stats);
    }

	/**
	* Runs the filters on the graph, returns true if all the filters return true, false otherwise.
	**/
    bool filter_check(const graphs::Graph<SpecificGraph>& g) const
    {
        auto should_solve = true;
        for (auto filter : filters)
        {
            should_solve &= filter->include_instance(g);
        }
        return should_solve;
    }

	/**
	* Runs the solvers on the specific graph, adds the results to stats.
	**/
    void solve_graph(const graphs::Graph<SpecificGraph>& g,
                     std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats,
                     std::mutex& stats_mutex) const
    {
        {
            auto scoped_lock = std::scoped_lock(stats_mutex);
            stats[g.edge_bits()] = std::vector<std::unique_ptr<InstanceSolution>>(); // this should be atomic.
        }
        for (const auto& solver : solvers)
        {
            std::unique_ptr<InstanceSolution> res;
            {
                auto scoped_lock = std::scoped_lock(stats_mutex);
                res = solver->solve(g);
            }
            {
				auto scoped_lock = std::scoped_lock(stats_mutex);
				stats[g.edge_bits()].push_back(std::move(res));
            }
        }
    }

	/**
	* For a specific v < SpecificGraph::vertices(), find all fundemental graphs based on previously v-1 found graphs.
	* It does so by running every permutation of adding a new node.
	**/
	void solve_specific_v(uint64_t specific_v,
                          std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats,
                          std::vector<uint64_t>& all_graphs,
                          std::mutex& all_graphs_mutex,
                          std::mutex& stats_mutex) const
    {
        const auto prev_size = all_graphs.size();
        const auto start = ((specific_v - 1) * (specific_v - 2) / 2);
        const auto number_of_perm = (1ULL << (specific_v - 1));

#pragma omp parallel for shared(all_graphs_mutex, stats_mutex, all_graphs, stats)
        for (auto idx = 0; idx < prev_size; idx++)
        {
            const auto prev_g = all_graphs[idx];
            for (uint64_t row_perm = 1; row_perm < number_of_perm; row_perm++)
            {
                auto instance = (row_perm << start) | prev_g;
                auto g = base_form(SpecificGraph(instance), specific_v);
                filter_and_solve_graph(g, stats, all_graphs, all_graphs_mutex, stats_mutex);
            }
        }
    }


	private:
	/**
	* Checks if the graph should be solved, and solves it if it should.
	**/
    void filter_and_solve_graph(const graphs::Graph<SpecificGraph>& g,
                      std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats,
                      std::vector<uint64_t>& all_graphs,
                      std::mutex& all_graphs_mutex,
                      std::mutex& stats_mutex) const
    {
        if (filter_check(g))
        {
            {
                auto scoped_lock = std::scoped_lock(all_graphs_mutex);
                all_graphs.push_back(g.edge_bits());
            }
            // std::cout << g.edges << std::endl;
            solve_graph(g, stats, stats_mutex);
        }
    }


    private:
    void print_stats(const std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& stats) const
    {
        constexpr uint64_t E = SpecificGraph::max_edges();
        std::cout << "Solutions:" << std::endl;
        for (const auto& pair : stats)
        {
            auto graph = pair.first;
            for (const auto& solution : pair.second)
            {
                std::cout << std::bitset<E>(graph) << " (" << graph << ") " << solution->best << std::endl;
            }
        }
        std::cout << stats.size() << std::endl;
    }
};
} // namespace npim