#include <iostream>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/max_independent_set.hpp>

namespace npim
{

void run()
{
    // auto g = Graph<5>(33554431);
    // std::cout << g << std::endl;

    auto solver = MaxIndependentSet();
    constexpr int v = 7;
    solver.solve<v, graphs::UGraph<v>>();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}