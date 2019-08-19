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
        graphs::DiGraph<5> g_modify = g_original.clone();
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("All zeros UGraph")
    {
        graphs::UGraph<5> g_original = graphs::UGraph<5>(0);
        graphs::UGraph<5> g_modify = g_original.clone();
        check_when_swap_has_no_change(g_original, g_modify);
    }


    TEST_CASE("All ones DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() - 1);
        auto g_modify = g_original.clone();
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("All ones UGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1);
        auto g_modify = g_original.clone();
        check_when_swap_has_no_change(g_original, g_modify);
    }

    TEST_CASE("Last index only DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(graphs::DiGraph<5>::number_of_graphs() / 2);
        auto g_modify = g_original.clone();
        auto service = IsomorphismService();

        service.swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() != g_modify.edge_bits());
    }

    TEST_CASE("Last index only UGraph swap has effect")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto g_modify = g_original.clone();
        auto service = IsomorphismService();

        service.swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() != g_modify.edge_bits());
    }

    TEST_CASE("Swap reverse DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(10503);
        auto g_modify = g_original.clone();
        check_swap_reverse_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap reverse UGraph")
    {
        auto g_original = graphs::UGraph<5>(503);
        auto g_modify = g_original.clone();
        check_swap_reverse_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap circle DiGraph")
    {
        auto g_original = graphs::DiGraph<5>(10503);
        auto g_modify = g_original.clone();
        check_swap_circle_has_no_effect(g_original, g_modify);
    }

    TEST_CASE("Swap circle UGraph")
    {
        auto g_original = graphs::UGraph<5>(503);
        auto g_modify = g_original.clone();
        check_swap_circle_has_no_effect(g_original, g_modify);
    }
}

TEST_SUITE("base_form")
{
    TEST_CASE("Zero is base form")
    {
        auto g_original = graphs::UGraph<5>(0);
        auto service = IsomorphismService();
        auto result = service.base_form(g_original);
        CHECK(g_original.edge_bits() == result.edge_bits());
    }

    TEST_CASE("All one is base form")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1);
        auto service = IsomorphismService();
        auto result = service.base_form(g_original);
        CHECK(g_original.edge_bits() == result.edge_bits());
    }

    TEST_CASE("Last one to first one")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto service = IsomorphismService();
        auto result = service.base_form(g_original);
        CHECK(result.edge_bits() == 1);
    }

    TEST_CASE("Base always lower or equal 1")
    {
        auto service = IsomorphismService();
        for (u_int64_t i = 0; i < graphs::UGraph<5>::number_of_graphs(); i++)
        {
            auto g_original = graphs::UGraph<5>(i);
            auto result = service.base_form(g_original);
            CHECK(result.edge_bits() <= i);
        }
    }

    // TEST_CASE("swap gives same base [Difficult]")
    // {
    //     auto service = IsomorphismService();
    //     auto g_original = graphs::UGraph<5>(938);

    //     auto result_before_swap = service.base_form(g_original);
    //     service.swap(g_original, 0, 2);
    //     auto result = service.base_form(g_original);
    //     std::cout << "Before: " << result_before_swap << std::endl;
    //     std::cout << "After: " << result << std::endl;
    //     CHECK(result.edge_bits() == result_before_swap.edge_bits());
    // }

    // TEST_CASE("swap gives same base [ALL]")
    // {
    //     auto service = IsomorphismService();
    //     for (u_int64_t i = 0; i < graphs::UGraph<5>::number_of_graphs(); i++)
    //     {
    //         auto g_original = graphs::UGraph<5>(i);

    //         auto result_before_swap = service.base_form(g_original);
    //         service.swap(g_original, 0, 2);
    //         auto result = service.base_form(g_original);

    //         CHECK(result.edge_bits() == result_before_swap.edge_bits());
    //         std::cout << i << std::endl;
    //     }
    // }
}
} // namespace npim