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
    for (auto g : graphs::GraphsRange<graphs::GraphIterator<graphs::UGraph<4>>>(0, 5))
    {
        std::cout << g << std::endl;
	}

    //auto iso_service = std::make_shared<IsomorphismService>();
    //auto solver = MaxIndependentSet(iso_service);
    //constexpr int v = 5;
    //solver.solve<graphs::UGraph<v>>();
}

} // namespace npim

int main()
{
    npim::run();
    return 0;
}