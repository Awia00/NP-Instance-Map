#pragma once
#include "graph_base.hpp"
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

    class GraphHolder
    {
        Graph<SpecificGraph> value_;

        public:
        GraphHolder(const Graph<SpecificGraph>& value) : value_(value)
        {
        }

        Graph<SpecificGraph> operator*()
        {
            return value_;
        }
    };

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

    GraphHolder operator++(int)
    {
        const auto ret = GraphHolder(SpecificGraph(value_));
        ++*this;
        return ret;
    }

    GraphIterator& operator++()
    {
        ++value_;
        return *this;
    }
};

template <class SpecificGraph>
class GraphsRange
{
    private:
    const int start_;
    const int end_;

    public:
    GraphsRange(int start, int end) : start_(start), end_(end)
    {
    }

    GraphIterator<SpecificGraph> begin()
    {
        return GraphIterator<SpecificGraph>(start_);
    }
    GraphIterator<SpecificGraph> end()
    {
        return GraphIterator<SpecificGraph>(end_);
    }
};


} // namespace graphs
}