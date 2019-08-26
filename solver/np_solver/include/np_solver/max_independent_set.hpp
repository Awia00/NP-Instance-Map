#pragma once
#include <bitset>
#include <cmath>
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/solution.hpp>
#include <unordered_set>
#include <vector>
#include <optional>

namespace npim
{
class MaxIndependentSet
{
    private:
    const std::shared_ptr<IsomorphismService> isomorph_service;

    public:
    MaxIndependentSet(std::shared_ptr<IsomorphismService> isomorph_service)
      : isomorph_service(std::move(isomorph_service))
    {
    }

    template <class GT>
    void solve()
    {
        constexpr uint64_t number_of_graphs = GT::number_of_graphs();
        std::cout << "Processing #" << number_of_graphs << " graphs" << std::endl;

        auto solutions = std::vector<std::optional<MaxIndependentSetSolution<GT::max_edges()>>>(number_of_graphs);

        auto iso_set = std::unordered_set<uint64_t>();
        for (uint64_t instance = 0; instance < number_of_graphs; instance++)
        {
            auto g = isomorph_service->base_form(GT(instance));
            if (iso_set.find(g.edge_bits()) != iso_set.end())
            {
                continue;
            }
            iso_set.insert(g.edge_bits());
            solutions[instance] = { solve_single<GT::max_edges(), GT>(g) };
        }

        auto counter = 0;
        for (const auto& opt_solution : solutions)
        {
            if (opt_solution)
            {
                auto solution = opt_solution.value();
                counter++;
                std::cout << solution.graph << " (" << solution.graph.to_ullong() << ") "
                          << solution.best << " " << solution.number_of_solutions << std::endl;
            }
        }
        std::cout << counter << std::endl;
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