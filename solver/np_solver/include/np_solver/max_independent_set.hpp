#pragma once
#include <bitset>
#include <cmath>
#include <np_solver/graph.hpp>

namespace npim
{

template <int V>
class MaxIndependentSet
{
    const uint64_t number_of_graphs = (1ULL << (V * V));

    public:
    MaxIndependentSet()
    {
    }

    void solve()
    {
        auto undirected_graphs = 0;
        for (uint64_t instance = 0; instance < number_of_graphs; instance++)
        {
            auto g = Graph<V>(instance);
            // TODO: find a smarter way to generate instances so we do not have to check for undirectedness.
            if (g.is_undirected())
            {
                undirected_graphs++;
                solve_single(g);
            }
        }
        std::cout << "#undirected graphs " << undirected_graphs << std::endl;
    }

    int solve_single(const Graph<V>& g) const
    {
        size_t counter = 0;
        size_t best = 0;

        auto number_of_solutions = 1 << V;
        std::cout << "G: " << g.edges << std::endl;
        // std::cout << g.string_representation() << std::endl;

        // std::cout << "Solutions:" << std::endl;
        for (auto i = 0; i < number_of_solutions; i++)
        {
            auto solution = std::bitset<V>(i);
            if (valid_solution(g, solution))
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

    bool valid_solution(const Graph<V>& g, const std::bitset<V>& solution) const
    {
        for (auto i = 0; i < V; i++)
        {
            if (solution[i])
            {
                for (auto j = 0; j < V; j++)
                {
                    if (i != j && solution[j] && (g.has_edge(i, j) || g.has_edge(j, i)))
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