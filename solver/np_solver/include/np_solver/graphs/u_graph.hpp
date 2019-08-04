#pragma once
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
namespace graphs
{

template <int V>
struct UGraph : Graph<UGraph<V>>
{
    private:
    const std::bitset<(V * (V - 1)) / 2> edges;

    public:
    constexpr static int vertices()
    {
        return V;
    }

    constexpr static uint64_t number_of_graphs()
    {
        return 1ULL << ((V * (V - 1)) / 2);
    }

    /**
     * edge_combination_bit is the number describing the bits that represent the activated edges.
     */
    UGraph(uint64_t edge_combination_bit)
      : edges(std::bitset<(V * (V - 1)) / 2>(edge_combination_bit))
    {
    }

    int index(int v1, int v2) const
    {
        return v1 * (v1 - 1) / 2 + v2;
    }

    bool has_edge(int v1, int v2) const
    {
        if (v1 == v2)
            return false;
        auto vlow = std::min(v1, v2);
        auto vhigh = std::max(v1, v2);
        return edges[index(vhigh, vlow)];
    }

    bool is_undirected() const
    {
        return true;
    }
};
} // namespace graphs
} // namespace npim