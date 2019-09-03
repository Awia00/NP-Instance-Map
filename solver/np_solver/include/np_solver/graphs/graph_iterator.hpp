#pragma once
#include "graph_base.hpp"
#include "u_graph.hpp"
#include "di_graph.hpp"
#include <iterator>

namespace npim
{

namespace graphs
{

template <class SpecificGraph>
class GraphIterator
{
    private:
    int value_;

    public:
    // Previously provided by std::iterator - see update below
    typedef Graph<SpecificGraph> value_type;
    typedef std::ptrdiff_t difference_type;
    typedef Graph<SpecificGraph>* pointer;
    typedef Graph<SpecificGraph>& reference;
    typedef std::input_iterator_tag iterator_category;

    explicit GraphIterator(int value) : value_(value)
    {
    }

    SpecificGraph operator*() const
    {
        return SpecificGraph(value_);
    }

    bool operator==(const GraphIterator& other) const
    {
        return value_ == other.value_;
    }

    bool operator!=(const GraphIterator& other) const
    {
        return !(*this == other);
    }

    SpecificGraph operator++(int)
    {
        const auto ret = SpecificGraph(value_);
        ++*this;
        return ret;
    }

    GraphIterator& operator++()
    {
        ++value_;
        return *this;
    }
};

template<int V>
using UGraphIterator = GraphIterator<UGraph<V>>;

template<int V>
using DiGraphIterator = GraphIterator<DiGraph<V>>;


template <class GraphIterator>
class GraphsRange
{
    private:
    const int start_;
    const int end_;

    public:
    GraphsRange(int start, int end) : start_(start), end_(end)
    {
    }

    GraphIterator begin() const
    {
        return GraphIterator(start_);
    }

    GraphIterator end() const
    {
        return GraphIterator(end_);
    }
};

} // namespace graphs
}