#pragma once
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
class IsomorphismService
{
    public:
    template <typename GT>
    void swap(const graphs::Graph<GT>& from, graphs::Graph<GT>& to, int v1, int v2) const
    {
        for (auto i = 0; i < GT::vertices; i++)
        {
            to.set_edge(i, v2, from.has_edge(i, v1));
            to.set_edge(i, v1, from.has_edge(i, v2));

            // to.set_edge(v2, i, from.has_edge(v1, i));
            // to.set_edge(v1, i, from.has_edge(v2, i));
        }
        std::cout << from << std::endl;
        std::cout << to << std::endl;
        // Swap the column of v1, and v2, and row of v1 and v2.
        // from and to are simply to avoid overriding
    }

    template <typename GT>
    bool are_isomorphic(const graphs::Graph<GT>& a, const graphs::Graph<GT>& b) const
    {
        // run all combinations of mappings of the vertices in A, and check if the bitset is equal
        //  to B.
        // A mapping is a swap of both row and col of the two swapping vertices.
        //  Values on the identity diagonal are copied to the others previous diagonal index.

        auto v = GT::vertices;
        auto number_of_mappings = 1ULL << (v * (v - 1)) / 2;
        for (auto i = 0; i < number_of_mappings; i++)
        {
            // find out which to swap (based on i)
        }

        return true;
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