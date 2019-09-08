#pragma once
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>
#include <unordered_set>
#include <vector>
#include <mutex>

namespace npim
{
namespace filters
{

template <class SpecificGraph>
class InstanceFilter
{
    public:
    virtual bool include_instance(const graphs::Graph<SpecificGraph>& g) = 0;
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
    bool include_instance(const graphs::Graph<SpecificGraph>& g) override
    {
        constexpr auto V = SpecificGraph::vertices();
        if (std::is_same<SpecificGraph, graphs::UGraph<SpecificGraph::vertices()>>::value)
        {
            /*if (!check_last_row_no_gaps(g)) {
                return false;
            }*/
        }
        return g.edge_bits() == base_form(g).edge_bits();
    }
};

template <class SpecificGraph>
class DuplicateFilter : public InstanceFilter<SpecificGraph>
{
    private:
    std::unordered_set<uint64_t> seen_graphs;
    std::mutex seen_graph_mutex{};

    public:
    bool include_instance(const graphs::Graph<SpecificGraph>& g) override
    {
        auto scoped_lock = std::scoped_lock(seen_graph_mutex);

        auto prev_size = this->seen_graphs.size();
        seen_graphs.insert(g.edge_bits());
        return prev_size != seen_graphs.size();
    }
};

template <class SpecificGraph>
class ConnectedGraphFilter : public InstanceFilter<SpecificGraph>
{
    private:
    std::unordered_set<uint64_t> seen_graphs;

    public:
    bool include_instance(const graphs::Graph<SpecificGraph>& g) override
    {
        return g.is_connected();
    }
};

} // namespace filters
} // namespace npim
