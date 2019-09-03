#pragma once
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/solution.hpp>
#include <np_solver/solvers/instance_solver.hpp>
#include <cmath>
#include <bitset>
#include <unordered_set>
#include <vector>
#include <optional>

namespace npim
{

	namespace solvers
{

template <class SpecificGraph>
class MaxIndependentSet : public InstanceSolver<SpecificGraph>
{
    public:
    MaxIndependentSet() = default;

    std::unique_ptr<InstanceSolution> solve(const graphs::Graph<SpecificGraph>& g) const override
    {
        constexpr auto V = g.vertices();
        size_t counter = 0;
        size_t best = 0;
        std::bitset<V> best_solution;

        auto number_of_solutions = 1 << V;
        for (auto i = 0; i < number_of_solutions; i++)
        {
            auto solution = std::bitset<V>(i);
            if (this->validate_solution(g, solution))
            {
                counter++;
                best = std::max(best, solution.count());
                best_solution = solution;
                //std::cout << "  " << solution << " size: " << solution.count() << std::endl;
            }
        }

        auto res = std::make_unique<MaxIndependentSetSolution<V>>();
        res->best = best;
        res->number_of_solutions = counter;
        res->solution = best_solution;
		return res;
    }

    bool validate_solution(const graphs::Graph<SpecificGraph>& g, const InstanceSolution& solution) const override
    {
        constexpr auto V = SpecificGraph::vertices();
        if constexpr (!std::is_same<InstanceSolution, MaxIndependentSetSolution<V>>::value)
        {
            return false;
        }
        else
        {
            auto solution_bitset = solution.solution;
            return validate_solution(solution_bitset);
		}
    }

	private:
    bool validate_solution(const graphs::Graph<SpecificGraph>& g, std::bitset<SpecificGraph::vertices()> solution) const
    {
        constexpr auto V = SpecificGraph::vertices();
		for (auto i = 0; i < V; i++)
        {
            if (solution[i])
            {
                for (auto j = i + 1; j < V; j++)
                {
                    if (solution[j] && (g.has_edge(i, j) || g.has_edge(j, i)))
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

} // namespace solvers

} // namespace npim