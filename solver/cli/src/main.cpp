#include <iostream>
#include <np_solver/dataset_repository.hpp>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>
#include <np_solver/max_independent_set.hpp>
#include <np_solver/graphs/graph_iterator.hpp>

namespace npim
{

void run()
{
    for (auto g : graphs::GraphsRange<graphs::UGraphIterator<3>>(0, 20))
    {
        std::cout << g << std::endl;
	}

    auto solver = MaxIndependentSet();
    constexpr int v = 5;
    solver.solve<graphs::UGraph<v>>();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}