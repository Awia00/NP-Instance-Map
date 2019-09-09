#pragma once
#include <bitset>

namespace npim
{

struct InstanceSolution
{
    // stats
    size_t best{ 0 };
    size_t number_of_solutions{ 0 };

    public:
    virtual void serialize() const = 0;
};

template <int V>
struct MaxIndependentSetSolution : public InstanceSolution
{
	// best solution
    std::bitset<V> solution{ 0 };
	
    void serialize() const override {
	// todo
	};
};


template <int V>
struct MaxCliqueSolution : public InstanceSolution
{
    // best solution
    std::bitset<V> solution{ 0 };

    void serialize() const override{
        // todo
    };
};
}