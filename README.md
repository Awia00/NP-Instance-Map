# NP-Instance-Map

I wish to create a dataset of all permutations of graphs and their corresponding solutions to some NP-Complete problems.

The idea with this project, is to explore if related graphs have related solutions or solution sizes.

Since the running time of this routine will be: ` O((n^2)! 2^n) ` I will only survey *very* small graphs.

## Supported NP-Complete problems
- Maximum Independent Set.

## Plan
- Create functionality for creating all permutations of a graph. This should be done such that one can create a specific graph from an integer.
- Create validation of a solution to the problems
- Solve the problem, potentially by bruteforce so we can see all solutions to the problem.
- Visualize the instances and their solutions somehow.
