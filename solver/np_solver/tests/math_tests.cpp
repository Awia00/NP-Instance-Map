#include <doctest/doctest.h>
#include <np_solver/math.hpp>

namespace npim
{
TEST_SUITE("factorial")
{
    // ====== TEST Helpers =====
    TEST_CASE("0")
    {
        CHECK(1 == factorial<0>());
    }

    TEST_CASE("negative")
    {
        CHECK(1 == factorial<-1>());
        CHECK(1 == factorial<-2>());
        CHECK(1 == factorial<-3>());
    }

    TEST_CASE("First 5")
    {
        CHECK(1 == factorial<1>());
        CHECK(2 == factorial<2>());
        CHECK(6 == factorial<3>());
        CHECK(24 == factorial<4>());
        CHECK(120 == factorial<5>());
    }

    TEST_CASE("result equals last result times new number")
    {
        auto last_result = 1;
        for (auto i = 2; i < 15; i++)
        {
            auto new_result = factorial<i>();
            CHECK(last_result * i == new_result);
            last_result = new_result;
        }
    }
}

TEST_SUITE("binomial coefficients")
{
    // ====== TEST Helpers =====
    TEST_CASE("0,0")
    {
        CHECK(1 == binomial<0, 0>());
    }

    TEST_CASE("x,0, x<5")
    {
        CHECK(1 == binomial<1, 0>());
        CHECK(1 == binomial<2, 0>());
        CHECK(1 == binomial<3, 0>());
        CHECK(1 == binomial<4, 0>());
    }

    TEST_CASE("0,y, y<5")
    {
        CHECK(0 == binomial<0, 1>());
        CHECK(0 == binomial<0, 2>());
        CHECK(0 == binomial<0, 3>());
        CHECK(0 == binomial<0, 4>());
    }

    TEST_CASE("x,y, x<5,y<5")
    {
        CHECK(1 == binomial<1, 1>());
        CHECK(0 == binomial<1, 2>());
        CHECK(0 == binomial<1, 3>());
        CHECK(0 == binomial<1, 4>());

        CHECK(2 == binomial<2, 1>());
        CHECK(1 == binomial<2, 2>());
        CHECK(0 == binomial<2, 3>());
        CHECK(0 == binomial<2, 4>());

        CHECK(3 == binomial<3, 1>());
        CHECK(3 == binomial<3, 2>());
        CHECK(1 == binomial<3, 3>());
        CHECK(0 == binomial<3, 4>());

        CHECK(4 == binomial<4, 1>());
        CHECK(6 == binomial<4, 2>());
        CHECK(4 == binomial<4, 3>());
        CHECK(1 == binomial<4, 4>());
    }
}
} // namespace npim