#pragma once
#include <bitset>
#include <stdint.h>
#include <stack>
#include <array>

namespace npim
{
namespace graphs
{
template <class SpecificGraph>
struct Graph
{
    public:
    constexpr static int vertices = SpecificGraph::vertices;
    constexpr static uint64_t max_edges = SpecificGraph::max_edges;

    constexpr static uint64_t number_of_graphs()
    {
        return SpecificGraph::number_of_graphs();
    }

    //

    bool has_edge(int v1, int v2) const
    {
        return static_cast<const SpecificGraph*>(this)->has_edge(v1, v2);
    }

    bool is_undirected() const
    {
        return static_cast<const SpecificGraph*>(this)->is_undirected();
    }
    
    bool is_connected() const {
        std::array<bool, vertices> visited = {false};
        std::stack<int> s;
        s.push(0);

        auto total = 0;
        while (!s.empty() && total != vertices) {
            auto active = s.top();
            visited[active] = true;
            s.pop();
            total++;
            for (auto i = 0; i<vertices; i++) {
                if (i != active && !visited[i] && has_edge(active, i)){
                    s.push(i);
                }
            }
        }
        return total == vertices;
    }

    int index(int v1, int v2) const
    {
        return static_cast<const SpecificGraph*>(this)->index(v1, v2);
    }

    uint64_t edge_bits() const
    {
        return static_cast<const SpecificGraph*>(this)->edge_bits();
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& obj)
{
    auto v = obj.vertices();
    os << "G(V=" << v << ", E={" << std::endl;
    for (auto i = 0; i < v; i++)
    {
        os << "   ";
        for (auto j = 0; j < v; j++)
        {
            os << obj.has_edge(i, j) << ", ";
        }
        os << std::endl;
    }
    return os << "})";
}
} // namespace graphs
} // namespace npim