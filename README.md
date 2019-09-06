# NP-Instance-Map

I wish to create a dataset of all permutations of graphs and their corresponding solutions to some NP-Complete problems.

The idea with this project, is to explore if related graphs have related solutions or solution sizes.

I suspect the running time of this routine to be: `O(2^((n*(n-1))/2) 2^n * O(f))` where f is the validation algorithm running time.
Therefore I will only survey _very_ small graphs.

## Supported NP-Complete problems

- Maximum Independent Set.

## Plan

- [x] Create functionality for creating all permutations of a graph. This should be done such that one can create a specific graph from an integer.
- [x] Create validation of a solution to the problems
- [x] Solve the problem, potentially by bruteforce so we can see all solutions to the problem.
- [ ] Serialize the dataset.
- [ ] Visualize the instances and their solutions somehow.
- [ ] Find an effective way to enumerate fundemental simple graphs / graph codes / canonical unlabbeled graphs.

## Visualization

- How many solutions are each node a part of (should be equal if we run on all symmetric graphs)
- How many solutions are
- What is the relationship between number of edges and solutions?
- What is the relationship between vertices degrees and solutions
- Based on different distance metrics between graphs (jacobian, isomorphism) map out size of solutions.
- Based on different distance metrics between solutions, map to graphs

## Enumerate Simple Unlabbeled graphs

Algorithms:

- [x] Run through all undirected graphs, check if they are in the min-code order. That is if they cannot be permuted to get a lower bitset representation. Runtime `O(2^(n(n-1)/2)) * O(n!)`
- [x] Take unlabelled fundemental graphs from n-1, run all permutations connections from of the new vertex on each of the previous fundemental graphs. Unsure of correctness of this. Runtime `O(n!/c) * O(2^n) * O(n!)`.
  - Should only have to make swaps on the having to enter the new row elements into the lower rows.
- [ ] Run all combinations of n-1 undirected graphs. Add rows to each of these where the row only allows 0's in leading positions. It has been seen that since the graph codes are in min-form that the last row never has a 0 after a 1 in the last row. Runtime `O(2^(n-1)*(n-2)/2) * n) * O(n!)`.
  - It most be possible to limit the swaps needed in veryfying the minimum idea for each of these graphs. Since we try all combinations of n-1 graphs and we know the last row is in its final form, we should be able to limit the swaps to those that do not affect the last row.
