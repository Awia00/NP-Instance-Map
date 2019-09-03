#pragma once
#include <iterator>
#include <np_solver/graphs/di_graph.hpp>
#include <np_solver/graphs/graph_base.hpp>
#include <np_solver/graphs/u_graph.hpp>
#include <np_solver/isomorphism.hpp>

namespace npim
{
namespace graphs
{

template <class SpecificGraph>
class GraphIterator
{
    protected:
    int _value;

    public:
    // Previously provided by std::iterator - see update below
    typedef Graph<SpecificGraph> _valuetype;
    typedef std::ptrdiff_t difference_type;
    typedef Graph<SpecificGraph>* pointer;
    typedef Graph<SpecificGraph>& reference;
    typedef std::input_iterator_tag iterator_category;

    explicit GraphIterator(int value) : _value(value)
    {
    }

    SpecificGraph operator*() const
    {
        return SpecificGraph(_value);
    }

    bool operator==(const GraphIterator<SpecificGraph>& other) const
    {
        return _value == other._value;
    }

    bool operator!=(const GraphIterator<SpecificGraph>& other) const
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
        ++_value;
        return *this;
    }
};


template <int V>
using UGraphIterator = GraphIterator<UGraph<V>>;

template <int V>
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
} // namespace npim