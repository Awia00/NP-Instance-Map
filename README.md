# NP-Instance-Map

I wish to create a dataset of all permutations of graphs and their corresponding solutions to some NP-Complete problems.

The idea with this project, is to explore if related graphs have related solutions or solution sizes.

I suspect the running time of this routine to be: `O(2^((n*(n-1))/2) 2^n * O(f))` where f is the validation algorithm running time.
Therefore I will only survey _very_ small graphs.

## Supported NP-Complete problems

- Maximum Independent Set.

## Plan

- Create functionality for creating all permutations of a graph. This should be done such that one can create a specific graph from an integer.
- Create validation of a solution to the problems
- Solve the problem, potentially by bruteforce so we can see all solutions to the problem.
- Visualize the instances and their solutions somehow.

## Visualization

- How many solutions are each node a part of (should be equal if we run on all symmetric graphs)
- How many solutions are
- What is the relationship between number of edges and solutions?
- What is the relationship between vertices degrees and solutions
- Based on different distance metrics between graphs (jacobian, isomorphism) map out size of solutions.
- Based on different distance metrics between solutions, map to graphs
