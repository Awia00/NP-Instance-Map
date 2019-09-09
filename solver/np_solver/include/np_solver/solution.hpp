#pragma once
#include <bitset>
#include <sstream>

namespace npim
{

struct InstanceSolution
{
    // stats
    const size_t best;
    const size_t number_of_solutions;
    InstanceSolution(size_t best, size_t number_of_solutions)
      : best(best), number_of_solutions(number_of_solutions)
    {
    }

    public:
    virtual std::string to_string() const = 0;
    virtual std::string header_string() const = 0;
};

template <int V>
struct MaxIndependentSetSolution : public InstanceSolution
{
	// best solution
    const std::bitset<V> solution;

	MaxIndependentSetSolution(size_t best, size_t number_of_solutions, const std::bitset<V>& solution)
      : InstanceSolution(best, number_of_solutions), solution(solution)
    {
    
	}
	
    std::string to_string() const override
    {
        std::stringstream ss;
        ss << best;
        return ss.str();
	};

    virtual std::string header_string() const override
    {
        return "max independent set";
    }
};


template <int V>
struct MaxCliqueSolution : public InstanceSolution
{
    // best solution
    const std::bitset<V> solution;

    MaxCliqueSolution(size_t best, size_t number_of_solutions, const std::bitset<V>& solution)
      : InstanceSolution(best, number_of_solutions), solution(solution)
    {
    }

    std::string to_string() const override
    {
        std::ostringstream ss;
        ss << best;
        return ss.str();
    };

    virtual std::string header_string() const override
    {
        return "max clique";
    }
};
}