#pragma once
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>

namespace npim
{
class IsomorphismService
{
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
        auto result = base.clone();
        bool has_changed = true;
        while (has_changed)
        {
            std::cout << result << std::endl;
            has_changed = false;
            for (auto i = 0; i < GT::vertices(); i++)
            {
                for (auto j = 0; j < GT::vertices(); j++)
                {
                    auto new_graph = result.clone();
                    swap(result, new_graph, i, j);
                    if (new_graph.edge_bits() < result.edge_bits())
                    {
                        // std::cout << "(" << i << ", " << j << ")" << std::endl;
                        result = new_graph;
                        has_changed = true;
                        break;
                    }
                }
                if (has_changed)
                {
                    break;
                }
            }
        }
        return result;
    }

    template <typename GT>
    bool are_isomorphic(const graphs::Graph<GT>& a, const graphs::Graph<GT>& b) const
    {
        // run all combinations of mappings of the vertices in A, and check if the bitset is equal
        //  to B.
        // A mapping is a swap of both row and col of the two swapping vertices.
        //  Values on the identity diagonal are copied to the others previous diagonal index.
        auto base_a = base_form(a);
        auto base_b = base_form(b);
        return base_a == base_b;
    }

    void online_isomorphism() const
    {
        // Create set of isomorhic graphs
        //
    }


    // TODO:
    // - function which checks if a new graphs is isomorphic with any previous graph.
    //     - should be possible online: keep a set of the bitset integers of all seen isomorphic graphs. Swap only the row/col of the outermost vertex, with all other vertices. Check each of these against the set.
    // note I have only looked at this for undirected graphs.
};
} // namespace npim