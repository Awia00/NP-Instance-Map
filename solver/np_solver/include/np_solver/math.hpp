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