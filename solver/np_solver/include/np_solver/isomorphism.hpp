#pragma once
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/math.hpp>
#include <tuple>
#include <vector>

namespace npim
{
template <typename GT>
void swap(const graphs::Graph<GT>& from, graphs::Graph<GT>& g, int v1, int v2)
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
void swap(graphs::Graph<GT>& g, int v1, int v2)
{
    if (v1 == v2)
    {
        return;
    }

    const GT from = g.clone();
    swap(from, g, v1, v2);
}

template <int V>
int perm_matrix(int col, int inst, std::array<int, V - 1> current_perm, std::vector<std::array<int, V - 1>>& perm_set)
{
    if (col < V)
    {
        inst = perm_matrix<V>(col + 1, inst, current_perm, perm_set); // zero recurse
        for (auto j = col; j < V - 1; j++)
        {
            current_perm[col] = j + 1;
            inst = perm_matrix<V>(col + 1, inst, current_perm, perm_set); // recurse
        }
    }
    else
    {
        perm_set.push_back(current_perm);
        return ++inst;
    }
    return inst;
}

template <int V>
constexpr std::vector<std::array<int, V - 1>> all_swap_combinations()
{
    // new Swap idea:
    // imagine a (v-1)*(v-1) matrix. A 1 in a position (i,j) means that vertex i,j will be swapped.
    // there must be atmost 1, in each row and colunm since we will not allow a i to be swapped
    // multiple times. one could therefore also just have a set of atmost v-1 pair of numbers
    // [0...v[ maybe (v choose 2)?

    auto perm_set = std::vector<std::array<int, V - 1>>();
    perm_set.reserve(factorial<V>());
    perm_matrix<V>(0, 0, std::array<int, V - 1>(), perm_set);
    // std::cout << "permsize: " << perm_set.size() << std::endl;

    return perm_set;
}

template <typename GT>
GT base_form(const graphs::Graph<GT>& base)
{
    auto swaps_set = all_swap_combinations<base.vertices()>();
    auto result = base.clone();

    for (const auto& swaps : swaps_set)
    {
        auto swapped = base.clone();
        for (auto i = 0; i < base.vertices() - 1; i++)
        {
            if (swaps[i] != 0)
            {
                swap(swapped, i, swaps[i]);
            }
        }
        if (swapped.edge_bits() < result.edge_bits())
        {
            result = swapped;
        }
    }
    return result;
}

template <typename GT>
bool are_isomorphic(const graphs::Graph<GT>& a, const graphs::Graph<GT>& b)
{
    auto base_a = base_form(a);
    auto base_b = base_form(b);
    return base_a == base_b;
}
} // namespace npim