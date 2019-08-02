#include <iostream>
#include <np_solver/graph.hpp>
#include <np_solver/max_independent_set.hpp>

namespace npim
{

void run()
{
    // auto g = Graph<5>(33554431);
    // std::cout << g << std::endl;

    auto solver = MaxIndependentSet<5>();
    solver.solve();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}