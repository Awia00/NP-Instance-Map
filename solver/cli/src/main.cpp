#include <iostream>
#include <np_solver/dataset_repository.hpp>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/graph_iterator.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>
#include <np_solver/permutation_runner.hpp>
#include <np_solver/solvers/max_independent_set.hpp>

namespace npim
{
void run()
{
    constexpr int v = 6;
    auto max_ind_set_solver = std::make_shared<solvers::MaxIndependentSet<graphs::UGraph<v>>>();
    // auto iso_filter = std::make_shared<filters::IsomorphFilter<graphs::UGraph<v>>>();
    auto duplicate_filter = std::make_shared<filters::DuplicateFilter<graphs::UGraph<v>>>();
    auto perm_runner = PermutationRunner<graphs::UGraph<v>>({ duplicate_filter }, { max_ind_set_solver });
    perm_runner.solve_all();
}
} // namespace npim

int main()
{
    npim::run();
    return 0;
}
