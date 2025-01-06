#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H

#include <vector>
#include <string>

/**
 * Class implementing the Greedy Algorithm for solving the Asymmetric Traveling Salesman Problem (ATSP).
 * The algorithm starts at each city, builds a tour greedily by selecting the nearest unvisited neighbor,
 * and returns the best tour among all starting points.
 */
class GreedyAlgorithm {
private:
    std::vector<std::vector<int>> distanceMatrix; ///< Adjacency matrix representing edge weights between cities.
    int matrixSize;                               ///< Number of cities in the matrix.
    std::vector<int> bestTour;                    ///< Best tour found by the algorithm.
    int bestCost;                                 ///< Cost of the best tour.

    /**
     * Builds a greedy solution starting from a specific city.
     * @param startCity The city from which to start the greedy algorithm.
     * @return The greedy tour starting from the given city.
     */
    std::vector<int> solveFromCity(int startCity);

    /**
     * Calculates the total cost of a given tour.
     * @param tour A vector representing the tour.
     * @return The total cost of the tour.
     */
    int calculateTourCost(const std::vector<int>& tour) const;

public:
    /**
     * Constructor for the GreedyAlgorithm class.
     * @param matrix The adjacency matrix representing edge weights between cities.
     */
    GreedyAlgorithm(const std::vector<std::vector<int>>& matrix);

    /**
     * Solves the ATSP using the greedy algorithm.
     * Starts from each city and selects the best tour.
     */
    void solve();

    /**
     * Retrieves the best tour found by the algorithm.
     * @return A vector representing the best tour.
     */
    std::vector<int> getBestTour() const;

    /**
     * Retrieves the cost of the best tour found by the algorithm.
     * @return The cost of the best tour.
     */
    int getBestCost() const;

    /**
     * Retrieves the number of vertices in the adjacency matrix.
     * @return The size of the adjacency matrix.
     */
    int getMatrixSize() const;

    /**
     * Saves the results (number of vertices and the best tour) to a file.
     * @param fileName The name of the file to save the results to.
     */
    void saveResultToFile(const std::string& fileName) const;
};

#endif

