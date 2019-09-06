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
        CHECK(GT::vertices() == 5);

        swap(g_modify, 0, 1);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 1);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());
    }

    template <typename GT>
    void check_swap_reverse_has_no_effect(const graphs::Graph<GT>& g_original, graphs::Graph<GT>& g_modify)
    {
        CHECK(GT::vertices() == 5);

        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 4);
        swap(g_modify, 4, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 1);
        swap(g_modify, 1, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());
    }

    template <typename GT>
    void check_swap_circle_has_no_effect(const graphs::Graph<GT>& g_original, graphs::Graph<GT>& g_modify)
    {
        CHECK(GT::vertices() == 5);

        swap(g_modify, 0, 1);
        swap(g_modify, 1, 2);
        swap(g_modify, 2, 0);
        swap(g_modify, 1, 2);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 4);
        swap(g_modify, 4, 3);
        swap(g_modify, 3, 2);
        swap(g_modify, 4, 3);
        CHECK(g_original.edge_bits() == g_modify.edge_bits());

        swap(g_modify, 2, 1);
        swap(g_modify, 1, 0);
        swap(g_modify, 0, 2);
        swap(g_modify, 1, 0);
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

        swap(g_modify, 2, 4);
        CHECK(g_original.edge_bits() != g_modify.edge_bits());
    }

    TEST_CASE("Last index only UGraph swap has effect")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto g_modify = g_original.clone();

        swap(g_modify, 2, 4);
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
        auto result = base_form(g_original);
        CHECK(g_original.edge_bits() == result.edge_bits());
    }

    TEST_CASE("All one is base form")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() - 1);
        auto result = base_form(g_original);
        CHECK(g_original.edge_bits() == result.edge_bits());
    }

    TEST_CASE("Last one to first one")
    {
        auto g_original = graphs::UGraph<5>(graphs::UGraph<5>::number_of_graphs() / 2);
        auto result = base_form(g_original);
        CHECK(result.edge_bits() == 1);
    }

    TEST_CASE("Base always lower or equal 1")
    {
        for (uint64_t i = 0; i < graphs::UGraph<5>::number_of_graphs(); i++)
        {
            auto g_original = graphs::UGraph<5>(i);
            auto result = base_form(g_original);
            CHECK(result.edge_bits() <= i);
        }
    }

    TEST_CASE("swap gives same base 1 [Difficult]")
    {
        auto g_original = graphs::UGraph<5>(938);

        auto result_before_swap = base_form(g_original);
        swap(g_original, 0, 2);
        auto result = base_form(g_original);
        CHECK(result.edge_bits() == result_before_swap.edge_bits());
    }

    TEST_CASE("swap gives same base 2 [Difficult]")
    {
        auto g_original = graphs::UGraph<5>(947);

        auto result_before_swap = base_form(g_original);
        swap(g_original, 0, 2);
        auto result = base_form(g_original);
        CHECK(result.edge_bits() == result_before_swap.edge_bits());
    }

    TEST_CASE("swap gives same base [ALL]")
    {
        for (uint64_t i = 0; i < graphs::UGraph<5>::number_of_graphs(); i++)
        {
            auto g_original = graphs::UGraph<5>(i);

            auto result_before_swap = base_form(g_original);
            swap(g_original, 0, 2);
            auto result = base_form(g_original);

            CHECK(result.edge_bits() == result_before_swap.edge_bits());
        }
    }

    TEST_CASE("First V=5 fundemental graphs")
    {
        CHECK(graphs::UGraph<5>(0).edge_bits() == base_form(graphs::UGraph<5>(0)).edge_bits());
        CHECK(graphs::UGraph<5>(1).edge_bits() == base_form(graphs::UGraph<5>(1)).edge_bits());
        CHECK(graphs::UGraph<5>(3).edge_bits() == base_form(graphs::UGraph<5>(3)).edge_bits());
        CHECK(graphs::UGraph<5>(7).edge_bits() == base_form(graphs::UGraph<5>(7)).edge_bits());
        CHECK(graphs::UGraph<5>(11).edge_bits() == base_form(graphs::UGraph<5>(11)).edge_bits());
        CHECK(graphs::UGraph<5>(12).edge_bits() == base_form(graphs::UGraph<5>(12)).edge_bits());
        CHECK(graphs::UGraph<5>(13).edge_bits() == base_form(graphs::UGraph<5>(13)).edge_bits());
        CHECK(graphs::UGraph<5>(15).edge_bits() == base_form(graphs::UGraph<5>(15)).edge_bits());
        CHECK(graphs::UGraph<5>(30).edge_bits() == base_form(graphs::UGraph<5>(30)).edge_bits());
        CHECK(graphs::UGraph<5>(31).edge_bits() == base_form(graphs::UGraph<5>(31)).edge_bits());
        CHECK(graphs::UGraph<5>(63).edge_bits() == base_form(graphs::UGraph<5>(63)).edge_bits());
        CHECK(graphs::UGraph<5>(75).edge_bits() == base_form(graphs::UGraph<5>(75)).edge_bits());
        CHECK(graphs::UGraph<5>(76).edge_bits() == base_form(graphs::UGraph<5>(76)).edge_bits());
        CHECK(graphs::UGraph<5>(77).edge_bits() == base_form(graphs::UGraph<5>(77)).edge_bits());
        CHECK(graphs::UGraph<5>(79).edge_bits() == base_form(graphs::UGraph<5>(79)).edge_bits());
        CHECK(graphs::UGraph<5>(86).edge_bits() == base_form(graphs::UGraph<5>(86)).edge_bits());
        CHECK(graphs::UGraph<5>(87).edge_bits() == base_form(graphs::UGraph<5>(87)).edge_bits());
        CHECK(graphs::UGraph<5>(94).edge_bits() == base_form(graphs::UGraph<5>(94)).edge_bits());
        CHECK(graphs::UGraph<5>(95).edge_bits() == base_form(graphs::UGraph<5>(95)).edge_bits());
        CHECK(graphs::UGraph<5>(116).edge_bits() == base_form(graphs::UGraph<5>(116)).edge_bits());
        CHECK(graphs::UGraph<5>(117).edge_bits() == base_form(graphs::UGraph<5>(117)).edge_bits());
        CHECK(graphs::UGraph<5>(119).edge_bits() == base_form(graphs::UGraph<5>(119)).edge_bits());
        CHECK(graphs::UGraph<5>(127).edge_bits() == base_form(graphs::UGraph<5>(127)).edge_bits());
        CHECK(graphs::UGraph<5>(222).edge_bits() == base_form(graphs::UGraph<5>(222)).edge_bits());
        CHECK(graphs::UGraph<5>(223).edge_bits() == base_form(graphs::UGraph<5>(223)).edge_bits());
        CHECK(graphs::UGraph<5>(235).edge_bits() == base_form(graphs::UGraph<5>(235)).edge_bits());
        CHECK(graphs::UGraph<5>(236).edge_bits() == base_form(graphs::UGraph<5>(236)).edge_bits());
        CHECK(graphs::UGraph<5>(237).edge_bits() == base_form(graphs::UGraph<5>(237)).edge_bits());
        CHECK(graphs::UGraph<5>(239).edge_bits() == base_form(graphs::UGraph<5>(239)).edge_bits());
        CHECK(graphs::UGraph<5>(254).edge_bits() == base_form(graphs::UGraph<5>(254)).edge_bits());
        CHECK(graphs::UGraph<5>(255).edge_bits() == base_form(graphs::UGraph<5>(255)).edge_bits());
        CHECK(graphs::UGraph<5>(507).edge_bits() == base_form(graphs::UGraph<5>(507)).edge_bits());
        CHECK(graphs::UGraph<5>(511).edge_bits() == base_form(graphs::UGraph<5>(511)).edge_bits());
        CHECK(graphs::UGraph<5>(1023).edge_bits() == base_form(graphs::UGraph<5>(1023)).edge_bits());
    }

    TEST_CASE("Some V=5 non-fundemental graphs")
    {
        CHECK(graphs::UGraph<5>(2).edge_bits() != base_form(graphs::UGraph<5>(2)).edge_bits());
        CHECK(graphs::UGraph<5>(4).edge_bits() != base_form(graphs::UGraph<5>(4)).edge_bits());
        CHECK(graphs::UGraph<5>(5).edge_bits() != base_form(graphs::UGraph<5>(5)).edge_bits());
        CHECK(graphs::UGraph<5>(6).edge_bits() != base_form(graphs::UGraph<5>(6)).edge_bits());
        CHECK(graphs::UGraph<5>(8).edge_bits() != base_form(graphs::UGraph<5>(8)).edge_bits());
        CHECK(graphs::UGraph<5>(9).edge_bits() != base_form(graphs::UGraph<5>(9)).edge_bits());
        CHECK(graphs::UGraph<5>(10).edge_bits() != base_form(graphs::UGraph<5>(10)).edge_bits());
        CHECK(graphs::UGraph<5>(14).edge_bits() != base_form(graphs::UGraph<5>(14)).edge_bits());
        CHECK(graphs::UGraph<5>(16).edge_bits() != base_form(graphs::UGraph<5>(16)).edge_bits());
        CHECK(graphs::UGraph<5>(64).edge_bits() != base_form(graphs::UGraph<5>(64)).edge_bits());
        CHECK(graphs::UGraph<5>(85).edge_bits() != base_form(graphs::UGraph<5>(85)).edge_bits());
        CHECK(graphs::UGraph<5>(118).edge_bits() != base_form(graphs::UGraph<5>(118)).edge_bits());
        CHECK(graphs::UGraph<5>(125).edge_bits() != base_form(graphs::UGraph<5>(125)).edge_bits());
    }
}
} // namespace npim
