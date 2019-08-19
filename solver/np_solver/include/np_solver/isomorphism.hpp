#pragma once
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <tuple>
#include <vector>

namespace npim
{
class IsomorphismService
{
    private:
    template <int value>
    constexpr u_int64_t factorial()
    {
        u_int64_t result = value;
        for (auto i = value - 1; i >= 1; i--)
        {
            result *= i;
        }
        return result;
    }

    public:
    template <typename GT>
    void swap(const graphs::Graph<GT>& from, graphs::Graph<GT>& g, int v1, int v2) const
    {
        if (v1 == v2)
        {
            return;
        }

        for (auto i = 0; i < GT::vertices(); i++)
        {
            g.set_edge(i, v2, from.has_edge(i, v1));
            g.set_edge(i, v1, from.has_edge(i, v2));
        }
        if constexpr (std::is_same<GT, graphs::UGraph<GT::vertices()>>())
        {
            g.set_edge(v1, v2, from.has_edge(v1, v2)); // case for UGraphs
        }
    }

    template <typename GT>
    void swap(graphs::Graph<GT>& g, int v1, int v2) const
    {
        if (v1 == v2)
        {
            return;
        }

        const GT from = g.clone();
        swap(from, g, v1, v2);
    }


    template <typename GT>
    GT base_form(const graphs::Graph<GT>& base)
    {
        auto swaps_set = std::vector<std::vector<std::tuple<int, int>>>();
        swaps_set.reserve(this->factorial<base.vertices()>());
        swaps_set.push_back({});

        for (auto i = 0; i < GT::vertices(); i++)
        {
            auto size = (int)swaps_set.size();
            for (auto j = i + 1; j < GT::vertices(); j++)
            {
                for (auto k = 0; k < size; k++)
                {
                    std::vector<std::tuple<int, int>> with = swaps_set[k];
                    with.push_back(std::make_tuple(i, j));
                    swaps_set.push_back(with);
                }
            }
        }
        auto result = base.clone();

        for (const auto& swaps : swaps_set)
        {
            auto swapped = base.clone();
            for (const auto& swap : swaps)
            {
                int v1 = std::get<0>(swap);
                int v2 = std::get<1>(swap);
                this->swap(swapped, v1, v2);
            }
            if (swapped.edge_bits() < result.edge_bits())
            {
                result = swapped;
            }
        }
        return result;
    }

    template <typename GT>
    bool are_isomorphic(const graphs::Graph<GT>& a, const graphs::Graph<GT>& b) const
    {
        auto base_a = base_form(a);
        auto base_b = base_form(b);
        return base_a == base_b;
    }
};
} // namespace npim