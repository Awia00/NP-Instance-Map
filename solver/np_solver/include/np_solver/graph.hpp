#pragma once
#include <bitset>
#include <sstream>
#include <stdint.h>

#define RM(row, col, width) row* width + col

namespace npim
{

template <int V>
struct Graph
{
    const std::bitset<V * V> edges;
    /**
     * edge_combination_bit is the number describing the bits that represent the activated edges.
     * For zero edges use 0, for all edges use 2^V -1, which coincidently also is the number of unique graphs.
     */
    Graph(uint64_t edge_combination_bit) : edges(std::bitset<V * V>(edge_combination_bit))
    {
    }

    constexpr int vertices() const
    {
        return V;
    }

    bool has_edge(int v1, int v2) const
    {
        return edges[RM(v1, v2, V)];
    }

    bool is_undirected() const
    {
        auto undirected = true;
        for (auto i = 0; i < V && undirected; i++)
        {
            undirected &= !has_edge(i, i);
            for (auto j = 0; j < V; j++)
            {
                undirected &= has_edge(i, j) == has_edge(j, i);
            }
        }
        return undirected;
    }

    std::string string_representation() const
    {
        std::stringstream ss;
        ss << "G(V=" << V << ", E={" << std::endl;
        for (auto i = 0; i < V; i++)
        {
            ss << "   ";
            for (auto j = 0; j < V; j++)
            {
                ss << edges[RM(i, j, V)] << ", ";
            }
            ss << std::endl;
        }
        ss << "})";
        return ss.str();
    }
};
} // namespace npim