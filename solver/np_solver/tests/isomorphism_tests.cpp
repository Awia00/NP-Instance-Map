#include <doctest/doctest.h>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/isomorphism.hpp>

namespace npim
{

TEST_SUITE("swap")
{
    TEST_CASE("Empty")
    {
        auto g_in = graphs::DiGraph<5>(0);
        graphs::Graph<graphs::DiGraph<5>> g_out = g_in; // copy

        auto service = IsomorphismService();
        service.swap(g_in, g_out, 0, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
        service.swap(g_in, g_out, 2, 4);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
        service.swap(g_in, g_out, 2, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
    }
}
} // namespace npim