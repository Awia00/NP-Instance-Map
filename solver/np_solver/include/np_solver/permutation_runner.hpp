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
class PermutationRunner
{
    protected:
    std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> filters;
    std::vector<std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> solvers;

    public:
    PermutationRunner(const std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>>& filters,
                      const std::vector<std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>>& solvers)
      : filters(filters), solvers(solvers)
    {
    }

    bool filter_check(const graphs::Graph<SpecificGraph>& g) const
    {
        auto should_solve = true;
        for (auto filter : filters)
        {
            should_solve &= filter->include_instance(g);
        }
        return should_solve;
    }

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

    void handle_graph(const graphs::Graph<SpecificGraph>& g,
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

    void solve_all() const
    {
        constexpr uint64_t V = SpecificGraph::vertices();
        constexpr uint64_t number_of_graphs = SpecificGraph::number_of_graphs();
        std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;

        auto stats = std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>();
        auto all_graphs = std::vector<uint64_t>();
        all_graphs.reserve(factorial<V>());

        auto all_graphs_mutex = std::mutex();
        auto stats_mutex = std::mutex();


        handle_graph(SpecificGraph(0), stats, all_graphs, all_graphs_mutex, stats_mutex); // add initial graph with 1 vertex, 0 edges.
        auto counter = 1;
        for (uint64_t i = 2; i <= V; i++)
        {
            std::cout << "V: " << i << std::endl;
            auto prev_size = all_graphs.size();

#pragma omp parallel for shared(all_graphs_mutex, stats_mutex, all_graphs, stats)
            for (auto idx = 0; idx < prev_size; idx++)
            {
                const auto prev_g = all_graphs[idx];
                const auto start = ((i - 1) * (i - 2) / 2);

                for (uint64_t row_perm = 1; row_perm < (1ULL << (i - 1)); row_perm++)
                {
                    auto instance = (row_perm << start) | prev_g;
                    auto g = base_form(SpecificGraph(instance), i);
                    handle_graph(g, stats, all_graphs, all_graphs_mutex, stats_mutex);
                }
            }
            std::cout << all_graphs.size() << std::endl;
        }
        std::cout << std::endl;
        print_stats(stats);
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