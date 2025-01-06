#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <vector>
#include <string>
#include <unordered_set>

/**
 * Class implementing the Tabu Search algorithm for solving the Traveling Salesman Problem (TSP).
 */
class TabuSearch {
private:
    std::vector<std::vector<int>> distanceMatrix; ///< Adjacency matrix representing distances between cities.
    int tabuLimit;                                 ///< Maximum size of the tabu list.
    double maxDuration;                      ///< Maximum allowed time for the algorithm to run.
    std::vector<int> optimalSolution;                    ///< Best tour found during the search.
    int optimalCost;                                 ///< Cost of the best tour.
    std::vector<int> currentSolution;                 ///< Current tour being evaluated.
    int currentSolutionCost;                              ///< Cost of the current tour.
    std::unordered_set<std::string> tabuList;     ///< Tabu list to avoid revisiting solutions.
    int iterationCounter;                           ///< Number of iterations performed.
    int noImprovementCount;                        ///< Counter to track stagnation in the search process.
    double bestSolutionTimestamp;                     ///< Timestamp when the best tour was found.

    /**
     * Calculates the total cost of a given tour.
     * @param tour A vector representing the tour.
     * @return The total cost of the tour.
     */
    int computeSolutionCost(const std::vector<int>& tour) const;

    /**
     * Converts a tour into a string representation for use as a key in the tabu list.
     * @param tour A vector representing the tour.
     * @return A string representation of the tour.
     */
    std::string tourToString(const std::vector<int>& tour) const;

    /**
     * Applies a 2-opt move to improve the tour.
     * @param tour A vector representing the current tour.
     */
    void applyTwoOpt(std::vector<int>& tour);

    /**
     * Applies a 3-opt move to improve the tour.
     * @param tour A vector representing the current tour.
     */
    void applyThreeOpt(std::vector<int>& tour);

    /**
     * Generates a set of promising neighbors based on the selected neighbor generation strategy.
     * @return A vector of tours representing the generated neighbors.
     */
    std::vector<std::vector<int>> generatePromisingNeighbors();

    /**
     * Evaluates the given neighbors and selects the best one that is not in the tabu list.
     * @param neighbors A vector of tours representing the neighbors.
     * @return The best neighbor tour.
     */
    std::vector<int> evaluateNeighbors(const std::vector<std::vector<int>>& neighbors);

    /**
     * Adds a tour to the tabu list. Removes the oldest entry if the tabu list exceeds its maximum size.
     * @param tour A vector representing the tour to be added to the tabu list.
     */
    void addToTabuList(const std::vector<int>& tour);

    /**
     * Diversifies the search by performing a partial shuffle of the current tour.
     */
    void diversifyWithPartialShuffle();

    /**
     * Initializes the current tour with a randomized greedy solution.
     */
    void initializeRandomizedGreedySolution();

public:
    /**
     * Constructor for TabuSearch.
     * @param matrix The distance matrix representing the TSP instance.
     * @param tabuSize The maximum size of the tabu list.
     * @param maxTimeInSeconds The maximum time allowed for the algorithm to run.
     * @param type The neighbor generation strategy to use (RANDOM, OPT_ONLY, or ADAPTIVE).
     */
    TabuSearch(const std::vector<std::vector<int>>& matrix, int tabuSize, double maxTimeInSeconds);

    /**
     * Runs the Tabu Search algorithm to solve the TSP.
     */
    void solve();

    std::vector<int> generateRandomSolution(int size) const;

    int computeSwapDelta(const std::vector<int>& solution, int i, int j) const;

    /**
     * Gets the best tour found during the search.
     * @return A vector representing the best tour.
     */
    std::vector<int> getOptimalSolution() const;

    /**
     * Gets the cost of the best tour found during the search.
     * @return The cost of the best tour.
     */
    int getOptimalCost() const;

    /**
     * Gets the timestamp when the best tour was found.
     * @return The timestamp in seconds since the start of the algorithm.
     */
    double getBestTourTimestamp() const;

    /**
     * Saves the results (number of vertices and best tour) to a file.
     * @param fileName The name of the file to save the results to.
     */
    void saveResultsToFile(const std::string& fileName) const;
};

#endif

