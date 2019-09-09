#pragma once 
#include <np_solver/graphs/graph_base.hpp>
#include <bitset>

namespace npim
{
namespace graphs
{
	template<class SpecificGraph>
	static int edge_edit_distance(const Graph<SpecificGraph>& g, const Graph<SpecificGraph>& other)
	{
        return std::bitset<SpecificGraph::max_edges()>(std::bit_xor(g.edge_bits(), other.edge_bits()))
            .count();
	}
}
}