#include <doctest/doctest.h>
#include <np_solver/graphs/di_graph.hpp>

namespace npim
{

TEST_SUITE("has_edge")
{
    TEST_CASE("Empty graph")
    {
        auto g = graphs::DiGraph<5>(0);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = 0; j < g.vertices(); j++)
            {
                CHECK(!g.has_edge(i, j));
            }
        }
    }

    TEST_CASE("Fully Connected Graph")
    {
        auto g = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() - 1); // all ones
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = 0; j < g.vertices(); j++)
            {
                CHECK(g.has_edge(i, j));
            }
        }
    }
}

TEST_SUITE("set_edge")
{
    TEST_CASE("can set_edge")
    {
        auto g = graphs::DiGraph<5>(10503);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = 0; j < g.vertices(); j++)
            {
                auto before = g.has_edge(i, j);
                g.set_edge(i, j, !before);
                auto after = g.has_edge(i, j);
                CHECK(after == !before);
            }
        }
    }

    TEST_CASE("set_edge reversible")
    {
        auto g = graphs::DiGraph<5>(10503);
        for (auto i = 0; i < g.vertices(); i++)
        {
            for (auto j = 0; j < g.vertices(); j++)
            {
                auto before = g.has_edge(i, j);
                g.set_edge(i, j, !before);
                g.set_edge(i, j, before);
                auto after = g.has_edge(i, j);
                CHECK(after == before);
            }
        }
    }
}
} // namespace npim