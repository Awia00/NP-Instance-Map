
#pragma once
#include <np_solver/filters/instance_filter.hpp>
#include <np_solver/solvers/instance_solver.hpp>
#include <np_solver/graphs/graph_base.hpp>
#include <map>

namespace npim
{


template <class SpecificGraph>
class PermutationRunner
{
    protected:
    std::vector<std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> filters;
    std::vector < std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> solvers;

	public:

    PermutationRunner(const std::vector < std::shared_ptr<filters::InstanceFilter<SpecificGraph>>> & filters,
                      const std::vector < std::shared_ptr<solvers::InstanceSolver<SpecificGraph>>> & solvers)
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

    void solve() const
    {
        constexpr uint64_t number_of_graphs = SpecificGraph::number_of_graphs();
        constexpr uint64_t E = SpecificGraph::max_edges();
        std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;
		
		auto stats = std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>();
        for (uint64_t instance = 0; instance < number_of_graphs; instance++)
        {
            auto g = SpecificGraph(instance);
            if (this->filter_check(g))
            {
                stats[instance] = std::vector<std::unique_ptr<InstanceSolution>>();
				for (const auto& solver : solvers) {
                    stats[instance].push_back(solver->solve(g));
				}
            }
        }

        for (const auto& pair : stats)
        {
            auto graph = pair.first;
            for (const auto& solution : pair.second)
            {
                std::cout << std::bitset<E>(graph) << " (" << graph <<
                    ") " << solution->best << " "
                          << solution->number_of_solutions << std::endl;
			}
            
        }
        std::cout << stats.size() << std::endl;
    }
};

} // namespace npim