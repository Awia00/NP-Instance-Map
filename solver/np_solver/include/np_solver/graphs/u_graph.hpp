#pragma once
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
namespace graphs
{
template <int V>
struct UGraph : Graph<UGraph<V>>
{
    constexpr const static int vertices()
    {
        return V;
    }
    constexpr const static int max_edges()
    {
        return ((V * (V - 1)) / 2);
    }

    private:
    std::bitset<max_edges()> edges;

    public:
    constexpr static uint64_t number_of_graphs()
    {
        return 1ULL << max_edges();
    }

    /**
     * edge_combination_bit is the number describing the bits that represent the activated edges.
     */
    UGraph(uint64_t edge_combination_bit) : edges(std::bitset<max_edges()>(edge_combination_bit))
    {
    }

    UGraph<V> clone() const
    {
        return UGraph<V>(edge_bits());
    }


    int index(int v1, int v2) const
    {
        auto vlow = std::min(v1, v2);
        auto vhigh = std::max(v1, v2);
        return vhigh * (vhigh - 1) / 2 + vlow;
    }

    void set_edge(int v1, int v2, bool val = true)
    {
        if (v1 == v2)
        {
            return;
        }
        edges.set(index(v1, v2), val);
    }

    bool has_edge(int v1, int v2) const
    {
        if (v1 == v2)
        {
            return false;
        }
        return edges[index(v1, v2)];
    }

    bool is_undirected() const
    {
        return true;
    }

    uint64_t edge_bits() const
    {
        return edges.to_ullong();
    }
};

} // namespace graphs
} // namespace npim