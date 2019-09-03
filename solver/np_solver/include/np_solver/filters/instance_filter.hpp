#pragma once 
#include <vector>
#include <np_solver/isomorphism.hpp>
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>

namespace npim
{
namespace filters
{

	template<class SpecificGraph>
    class InstanceFilter
    {
        public:

        virtual bool include_instance(const graphs::Graph<SpecificGraph>& g) const = 0;
	};

	template <class SpecificGraph>
    class IsomorphFilter : public InstanceFilter<SpecificGraph>
    {
        private: 
		bool check_last_row_no_gaps(const graphs::Graph<SpecificGraph>& g) const
        {
            constexpr auto V = SpecificGraph::vertices();
            for (auto i = V - 1; i >= 0; i--)
            {
                auto seen_one = false;
                for (auto j = V - 1; j >= i + 1; j--)
                {
                    if (g.has_edge(i, j))
                    {
                        seen_one = true;
                    }
                    else if (seen_one)
                    {
                        return false;
                    }
                }
                if (seen_one)
                {
                    break;
                }
            }
            return true;
        }

        public:
        bool include_instance(const graphs::Graph<SpecificGraph>& g) const override
        {
            constexpr auto V = SpecificGraph::vertices();
            if (std::is_same<SpecificGraph, graphs::UGraph<SpecificGraph::vertices()>>::value)
            {
				if (!check_last_row_no_gaps(g)) {
                    return false;
				}
			}
            return g.edge_bits() == base_form(g).edge_bits();
		}
	};
    }
}