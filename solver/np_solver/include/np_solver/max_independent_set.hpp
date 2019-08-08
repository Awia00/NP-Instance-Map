#pragma once
#include <bitset>
#include <cmath>
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/solution.hpp>
#include <vector>

namespace npim
{
class MaxIndependentSet
{
    public:
    MaxIndependentSet()
    {
    }

    template <class GT>
    void solve()
    {
        const uint64_t number_of_graphs = GT::number_of_graphs();
        std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;

        auto undirected_graphs = 0;
        auto solutions = std::vector<MaxIndependentSetSolution<GT::max_edges()>>(number_of_graphs);

#pragma omp parallel for
        for (uint64_t instance = 0; instance < number_of_graphs; instance++)
        {
            auto g = GT(instance);
            if (g.is_undirected())
            {
                undirected_graphs++;
                solutions[instance] = (solve_single<GT::max_edges(), GT>(g));
            }
        }

        for (const auto& solution : solutions)
        {
            if (solution.graph != 0)
            {
                std::cout << solution.graph << " (" << solution.graph.to_ullong() << ") "
                          << solution.best << " " << solution.number_of_solutions << std::endl;
            }
        }
    }

    template <int M, class GT>
    MaxIndependentSetSolution<M> solve_single(const graphs::Graph<GT>& g) const
    {
        size_t counter = 0;
        size_t best = 0;
        constexpr auto V = g.vertices();

        auto number_of_solutions = 1 << V;
        for (auto i = 0; i < number_of_solutions; i++)
        {
            auto solution = std::bitset<V>(i);
            if (valid_solution<V>(g, solution))
            {
                counter++;
                best = std::max(best, solution.count());
                // std::cout << "  " << solution << " size: " << solution.count() << std::endl;
            }
        }
        return { g.edge_bits(), best, counter };
    }

    template <int V, class GT>
    bool valid_solution(const graphs::Graph<GT>& g, const std::bitset<V>& solution) const
    {
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
} // namespace npim