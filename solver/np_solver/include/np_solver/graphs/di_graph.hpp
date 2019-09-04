#pragma once
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
namespace graphs
{
template <int V>
struct DiGraph : public Graph<DiGraph<V>>
{
    constexpr const static int vertices()
    {
        return V;
    }
    constexpr const static int max_edges()
    {
        return V * V;
    }

    private:
    std::bitset<max_edges()> edges;

    public:
    constexpr static uint64_t number_of_graphs()
    {
        return 1ULL << (max_edges());
    }
    /**
     * edge_combination_bit is the number describing the bits that represent the activated edges.
     * For zero edges use 0, for all edges use 2^V -1, which coincidently also is the number of unique graphs.
     */
    DiGraph(uint64_t edge_combination_bit) : edges(std::bitset<max_edges()>(edge_combination_bit))
    {
    }

    DiGraph<V> clone() const
    {
        return DiGraph<V>(edge_bits());
    }

    void set_edge(int v1, int v2, bool val = true)
    {
        edges.set(index(v1, v2), val);
    }

    bool has_edge(int v1, int v2) const
    {
        return edges[index(v1, v2)];
    }

    int index(int v1, int v2) const
    {
        return v1 * V + v2;
    }

    bool is_undirected() const
    {
        auto undirected = true;
        for (auto i = 0; i < V && undirected; i++)
        {
            undirected &= !has_edge(i, i);
            for (auto j = i + 1; j < V; j++)
            {
                undirected &= has_edge(i, j) == has_edge(j, i);
            }
        }
        return undirected;
    }

    uint64_t edge_bits() const
    {
        return edges.to_ullong();
    }
};
} // namespace graphs
} // namespace npim