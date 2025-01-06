#include "../headers/GreedyAlgorithm.h"

#include <fstream>
#include <unordered_set>
#include <numeric>
#include <limits>
#include <algorithm>

// Constructor
GreedyAlgorithm::GreedyAlgorithm(const std::vector<std::vector<int>>& matrix) 
    : distanceMatrix(matrix), 
      matrixSize(matrix.size()), 
      bestCost(std::numeric_limits<int>::max()) {}

// Build a greedy solution starting from a specific city
std::vector<int> GreedyAlgorithm::solveFromCity(int startCity) {
    std::vector<int> tour;
    std::unordered_set<int> visited;

    int currentCity = startCity;
    tour.push_back(currentCity);
    visited.insert(currentCity);

    for (int step = 1; step < matrixSize; ++step) {
        int nextCity = -1;
        int minDistance = std::numeric_limits<int>::max();

        for (int city = 0; city < matrixSize; ++city) {
            if (visited.find(city) == visited.end() && distanceMatrix[currentCity][city] < minDistance) {
                minDistance = distanceMatrix[currentCity][city];
                nextCity = city;
            }
        }

        if (nextCity != -1) {
            currentCity = nextCity;
            tour.push_back(currentCity);
            visited.insert(currentCity);
        }
    }

    tour.push_back(tour.front()); 
    return tour;
}

// Calculate the cost of a given tour
int GreedyAlgorithm::calculateTourCost(const std::vector<int>& tour) const {
    int totalCost = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += distanceMatrix[tour[i]][tour[i + 1]];
    }
    return totalCost;
}

// Solve the ATSP using the greedy algorithm
void GreedyAlgorithm::solve() {
    for (int startCity = 0; startCity < matrixSize; ++startCity) {
        std::vector<int> tour = solveFromCity(startCity);
        int totalCost = calculateTourCost(tour);

        if (totalCost < bestCost) {
            bestCost = totalCost;
            bestTour = tour;
        }
    }
}

// Get the best tour
std::vector<int> GreedyAlgorithm::getBestTour() const {
    return bestTour;
}

// Get the best cost
int GreedyAlgorithm::getBestCost() const {
    return bestCost;
}

// Get the matrix size
int GreedyAlgorithm::getMatrixSize() const {
    return matrixSize;
}

// Save results to a file
void GreedyAlgorithm::saveResultToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName);

    if (!outFile) {
        throw std::runtime_error("Error: Unable to open file for writing.");
    }

    // Write number of vertices
    outFile << matrixSize << std::endl;

    // Write best tour
    for (int city : bestTour) {
        outFile << city << " ";
    }
    outFile << std::endl;

    outFile.close();
}

