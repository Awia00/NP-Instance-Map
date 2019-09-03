#pragma once

template <int value>
constexpr uint64_t factorial()
{
    uint64_t result = value;
    for (auto i = value - 1; i >= 1; i--)
    {
        result *= i;
    }
    return result;
}

template <int n, int k>
constexpr uint64_t binomial_coefficient()
{
    auto fact_n = factorial<n>();
    auto fact_k = factorial<k>();
    auto fact_n_minus_k = factorial<n - k>();
    return fact_n / (fact_k * fact_n_minus_k);
}