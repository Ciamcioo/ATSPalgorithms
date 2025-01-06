// SimulatedAnnealing.h
#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <string>

/**
 * Class: SimulatedAnnealing
 * --------------------------
 * Implements the Simulated Annealing algorithm for solving the Asymmetric Traveling Salesman Problem (ATSP).
 * The algorithm iteratively improves the solution by exploring the search space while avoiding local minima
 * through probabilistic acceptance of worse solutions. The temperature decreases over time based on a cooling factor.
 */
class SimulatedAnnealing {
private:
    /**
     * Adjacency matrix representing distances between nodes in the graph.
     */
    const std::vector<std::vector<int>>& graph;

    /**
     * Cooling rate used to decrease the temperature.
     * Typical values are between 0.8 and 0.99.
     */
    double coolingFactor;

    /**
     * Maximum time allowed for the algorithm to run, in seconds.
     */
    double maxTime;

    /**
     * Number of nodes in the graph.
     */
    int graphSize;

    /**
     * Cost of the current solution.
     */
    int currentCost;

    /**
     * Current solution being evaluated.
     */
    std::vector<int> currentSolution;

    /**
     * Cost of the best solution found during the search.
     */
    int bestCost;

    /**
     * Best solution found during the search.
     */
    std::vector<int> bestSolution;

    /**
     * Timestamp (in seconds) when the best solution was found.
     */
    double bestSolutionTimestamp;

    /**
     * Calculates the total cost of a given solution.
     * @param solution The current solution represented as a sequence of node indices.
     * @param adjacencyMatrix The graph's adjacency matrix.
     * @param dimension The number of nodes in the graph.
     * @return The total cost of the solution.
     */
    int calculateCost(const std::vector<int>& solution, std::vector<std::vector<int>> adjacencyMatrix, int dimension);

    /**
     * Runs the Simulated Annealing algorithm for a given initial solution.
     * @param initialSolution The starting solution for the algorithm.
     */
    void runSimulatedAnnelingFor(std::vector<int> initialSolution);

public:
    /**
     * Constructor for SimulatedAnnealing.
     * @param graph The graph's adjacency matrix representing distances between nodes.
     * @param coolingFactor The cooling rate for the algorithm.
     * @param maxTime The maximum time allowed for the algorithm to run.
     */
    SimulatedAnnealing(const std::vector<std::vector<int>>& graph, double coolingFactor, double maxTime);

    /**
     * Executes the Simulated Annealing algorithm to find the optimal solution.
     */
    void solve();

    /**
     * Retrieves the best solution found during the search.
     * @return The best solution as a sequence of node indices.
     */
    std::vector<int> getBestSolution() const;

    /**
     * Retrieves the cost of the best solution found during the search.
     * @return The cost of the best solution.
     */
    int getBestCost() const;

    /**
     * Retrieves the timestamp when the best solution was found.
     * @return The timestamp in seconds since the start of the algorithm.
     */
    double getBestSolutionTimestamp() const;

    /**
     * Saves the results (best solution and its cost) to a specified file.
     * @param fileName The name of the file to save the results to.
     */
    void saveResultsToFile(const std::string& fileName) const;
};

#endif // SIMULATED_ANNEALING_H

