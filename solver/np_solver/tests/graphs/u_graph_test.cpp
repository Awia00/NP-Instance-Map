#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <np_solver/graphs/u_graph.hpp>

namespace npim
{
TEST_CASE("Testing has_edge on empty graph")
{
    auto g = graphs::UGraph<5>(0);
    for (auto i = 0; i < g.vertices; i++)
    {
        for (auto j = i + 1; j < g.vertices; j++)
        {
            CHECK(!g.has_edge(i, j));
            CHECK(!g.has_edge(j, i));
            CHECK(g.index(i, j) == g.index(j, i));
        }
    }
}

TEST_CASE("Testing index is same for (i,j) and (j,i)")
{
    auto g = graphs::UGraph<5>(0);
    for (auto i = 0; i < g.vertices; i++)
    {
        for (auto j = i + 1; j < g.vertices; j++)
        {
            CHECK(g.index(i, j) == g.index(j, i));
        }
    }
}

TEST_CASE("Testing has_edge is true for all edeges")
{
    auto g = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1); // all ones
    for (auto i = 0; i < g.vertices; i++)
    {
        for (auto j = i + 1; j < g.vertices; j++)
        {
            CHECK(g.has_edge(i, j));
            CHECK(g.has_edge(j, i));
        }
    }
}
} // namespace npim