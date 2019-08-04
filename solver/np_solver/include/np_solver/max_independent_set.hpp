#pragma once
#include <bitset>
#include <cmath>
#include <np_solver/graphs/graph_base.hpp>

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

        auto undirected_graphs = 0;
        for (uint64_t instance = 0; instance < number_of_graphs; instance++)
        {
            auto g = GT(instance);
            // TODO: find a smarter way to generate instances so we do not have to check for undirectedness.
            if (g.is_undirected())
            {
                undirected_graphs++;
                solve_single<GT>(g);
            }
        }
        std::cout << "#undirected graphs " << undirected_graphs << std::endl;
    }

    template <class GT>
    int solve_single(const graphs::Graph<GT>& g) const
    {
        constexpr auto V = g.vertices();
        size_t counter = 0;
        size_t best = 0;

        auto number_of_solutions = 1 << V;
        // std::cout << "G: " << g.edges << std::endl;
        std::cout << g << std::endl;

        // std::cout << "Solutions:" << std::endl;
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
        std::cout << "#Solutions: " << counter << ", Best: " << best << std::endl;
        std::cout << std::endl;
        return best;
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