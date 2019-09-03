#pragma once 
#include <vector>
#include <np_solver/isomorphism.hpp>
#include <np_solver/graphs/graph_base.hpp>

namespace npim
{
namespace filters
{

	template<class SpecificGraph>
    class InstanceFilter
    {
        public:

        virtual bool include_instance(const graphs::Graph<SpecificGraph>& graph) const = 0;
	};

	template <class SpecificGraph>
    class IsomorphFilter : public InstanceFilter<SpecificGraph>
    {
        public:
        bool include_instance(const graphs::Graph<SpecificGraph>& graph) const override
        {
            return graph.edge_bits() == base_form(graph).edge_bits();
		}
	};
    }
}