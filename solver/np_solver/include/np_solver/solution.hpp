#pragma once
#include <bitset>

namespace npim
{

template <int V>
struct MaxIndependentSetSolution
{
    std::bitset<V> graph{ 0 };
    size_t best{ 0 };
    size_t number_of_solutions{ 0 };
};

}