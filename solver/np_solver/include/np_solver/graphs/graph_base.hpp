#pragma once
#include <bitset>
#include <stdint.h>

namespace npim
{
namespace graphs
{
template <class SpecificGraph>
struct Graph
{
    public:
    constexpr static int vertices()
    {
        return SpecificGraph::vertices();
    }

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

    int index(int v1, int v2) const
    {
        return static_cast<const SpecificGraph*>(this)->index(v1, v2);
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