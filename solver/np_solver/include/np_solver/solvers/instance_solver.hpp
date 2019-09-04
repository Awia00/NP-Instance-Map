#pragma once
#include <np_solver/solution.hpp>
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
namespace solvers
{

template <class SpecificGraph>
class InstanceSolver
{
    public:
    virtual std::unique_ptr<InstanceSolution> solve(const graphs::Graph<SpecificGraph>& graph) const = 0;

    virtual bool validate_solution(const graphs::Graph<SpecificGraph>& graph,
                                   const InstanceSolution& solution) const = 0;
};

}
}