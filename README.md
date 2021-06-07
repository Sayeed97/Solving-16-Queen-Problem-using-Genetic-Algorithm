# Breif: 
The 16 Queen is the problem of placing 16 chess queens on an 16×16 chessboard so that no two queens attack each other. 

`Naive Algorithm:` Generate all possible configurations of queens on board and print a configuration that satisfies the given constraints.

`Genetic Algorithm:` Generate different configurations of queens on board based on cross-over and mutation rate and print a configuration that statisfies the given constraints.

`Naive Algorithm vs Genetic Algorithm -` Naive algorithm searches through the entire search space whereas Genetic algorithm effectively searches through the search space based on the fitness of the solutions. 

# Test Environment: 
* Compiler - onlinegdb.com (online C++ compiler)
* Text Editor - Notepad++

# Repository Contents: 
- 16-Queen Problem.pptx -  A Powerpoint presentation about the code and its theory 

- main.c - Source code

# Genetic Algorithm: 
A genetic algorithm is a search heuristic that is inspired by Charles Darwin’s theory of natural evolution. This algorithm reflects the process of natural selection where the fitest solutions are selected for cross-over in order to produce new solutions of the next generation.

# Code Sequence: 
1. Parent generation 
2. Fitness calculation 
3. Tournament selection is used to select the best parent for cross-over process
4. Cross-over operation (PMX)
5. Mutation operation (Activation of this operation depends on the mutation rate)
6. Cross-over and mutation operation together generates the next generation solutions
7. Check if any solution has fitness value 0, if false repeat from step 2
8. Prints the optimal solution
