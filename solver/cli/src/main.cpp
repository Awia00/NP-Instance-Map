#include <iostream>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/max_independent_set.hpp>

namespace npim
{

void run()
{
    auto solver = MaxIndependentSet();
    constexpr int v = 6;
    solver.solve<graphs::UGraph<v>>();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}