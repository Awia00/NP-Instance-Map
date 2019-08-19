#include <iostream>
#include <np_solver/dataset_repository.hpp>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>
#include <np_solver/max_independent_set.hpp>

namespace npim
{

void run()
{
    auto iso_service = std::make_shared<IsomorphismService>();
    auto solver = MaxIndependentSet(iso_service);
    constexpr int v = 5;
    solver.solve<graphs::UGraph<v>>();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}