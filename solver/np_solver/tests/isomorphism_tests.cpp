#include <doctest/doctest.h>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/isomorphism.hpp>

namespace npim
{

TEST_SUITE("swap")
{
    TEST_CASE("All zeros")
    {
        graphs::DiGraph<5> g_in = graphs::DiGraph<5>(0);
        auto service = IsomorphismService();

        auto g_out = service.swap(g_in, 0, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());

        g_out = service.swap(g_in, 2, 4);
        CHECK(g_in.edge_bits() == g_out.edge_bits());

        g_out = service.swap(g_in, 2, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
    }

    TEST_CASE("All ones")
    {
        auto g_in = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() - 1);
        auto service = IsomorphismService();

        auto g_out = service.swap(g_in, 0, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());

        g_out = service.swap(g_in, 2, 4);
        CHECK(g_in.edge_bits() == g_out.edge_bits());

        g_out = service.swap(g_in, 2, 1);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
    }

    TEST_CASE("Swap reverse")
    {
        auto g_in = graphs::DiGraph<5>(10503);
        auto service = IsomorphismService();

        auto g_out = service.swap(g_in, 0, 1);
        g_out = service.swap(g_out, 1, 0);
        CHECK(g_in.edge_bits() == g_out.edge_bits());
        std::cout << g_in << std::endl;
        std::cout << g_out << std::endl;

        // service.swap(g_in, g_out, 2, 4);
        // service.swap(g_out, g_out, 4, 2);
        // CHECK(g_in.edge_bits() == g_out.edge_bits());
        // std::cout << g_in << std::endl;
        // std::cout << g_out << std::endl;

        // service.swap(g_in, g_out, 2, 1);
        // service.swap(g_out, g_out, 1, 2);
        // CHECK(g_in.edge_bits() == g_out.edge_bits());
        // std::cout << g_in << std::endl;
        // std::cout << g_out << std::endl;
    }
}
} // namespace npim