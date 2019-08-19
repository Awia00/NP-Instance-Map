#include <doctest/doctest.h>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>

namespace npim
{

TEST_SUITE("swap")
{
    // ====== TEST Helpers =====

    template <typename GT>
    void check_when_swap_has_no_change(const graphs::Graph<GT>& g_original, graphs::Graph<GT>& g_modify)
    {
        auto service = IsomorphismService();
        CHECK(GT::vertices() == 5);

        service.swap(g_modify, 0, 1);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 1);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());
    }

    template <typename GT>
    void check_swap_reverse_has_no_effect(const graphs::Graph<GT>& g_original, graphs::Graph<GT>& g_modify)
    {
        CHECK(GT::vertices() == 5);

        auto service = IsomorphismService();

        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 4);
        service.swap(g_modify, 4, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 1);
        service.swap(g_modify, 1, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());
    }

    template <typename GT>
    void check_swap_circle_has_no_effect(const graphs::Graph<GT>& g_original, graphs::Graph<GT>& g_modify)
    {
        CHECK(GT::vertices() == 5);

        auto service = IsomorphismService();

        service.swap(g_modify, 0, 1);
        service.swap(g_modify, 1, 2);
        service.swap(g_modify, 2, 0);
        service.swap(g_modify, 1, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 4);
        service.swap(g_modify, 4, 3);
        service.swap(g_modify, 3, 2);
        service.swap(g_modify, 4, 3);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        service.swap(g_modify, 2, 1);
        service.swap(g_modify, 1, 0);
        service.swap(g_modify, 0, 2);
        service.swap(g_modify, 1, 0);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());
    }

    // ====== TEST CASES =====

    TEST_CASE("All zeros DiGraph")
    {
        graphs::DiGraph<5> g_original = graphs::DiGraph<5>(0);
        graphs::DiGraph<5> g_modify = graphs::DiGraph<5>(0);
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("All zeros UGraph")
    {
        graphs::UGraph<5> g_original = graphs::UGraph<5>(0);
        graphs::UGraph<5> g_modify = graphs::UGraph<5>(0);
        check_when_swap_has_no_change(g_original, g_modify);
    }


    TEST_CASE("All ones DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() - 1);
        auto g_modify = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() - 1);
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("All ones UGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1);
        auto g_modify = graphs::DiGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1);
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("Last index only DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() / 2);
        auto g_modify = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() / 2);
        auto service = IsomorphismService();

        service.swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() != g_modify.edge_bits());
    }

    TEST_CASE("Last index only UGraph")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto g_modify = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto service = IsomorphismService();

        service.swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() != g_modify.edge_bits());
    }

    TEST_CASE("Swap reverse DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(10503);
        auto g_modify = graphs::DiGraph<5>(10503);
        check_swap_reverse_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap reverse UGraph")
    {
        auto g_original = graphs::UGraph<5>(503);
        auto g_modify = graphs::UGraph<5>(503);
        check_swap_reverse_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap circle DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(10503);
        auto g_modify = graphs::DiGraph<5>(10503);
        check_swap_circle_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap circle UGraph")
    {
        auto g_original = graphs::UGraph<5>(503);
        auto g_modify = graphs::UGraph<5>(503);
        check_swap_circle_has_no_effect(g_original, g_modify);
    }
}
} // namespace npim