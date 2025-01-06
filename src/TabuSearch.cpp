#include "../headers/TabuSearch.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <unordered_set>
#include <numeric>

// Constructor
TabuSearch::TabuSearch(const std::vector<std::vector<int>>& matrix, int tabuLimit, double maxDuration) 
    : distanceMatrix(matrix), tabuLimit(tabuLimit), maxDuration(maxDuration) {
    optimalCost = std::numeric_limits<int>::max();
    currentSolutionCost = 0;
    iterationCounter = 0;
    noImprovementCount = 0;
    bestSolutionTimestamp = 0.0;

    currentSolution.resize(matrix.size());
    optimalSolution.resize(matrix.size());
}

// Calculate the cost of a tour
int TabuSearch::computeSolutionCost(const std::vector<int>& solution) const {
    int cost = 0;

    for (size_t i = 0; i < solution.size() - 1; ++i) {
        cost += distanceMatrix[solution[i]][solution[i + 1]];
    }

    cost += distanceMatrix[solution.back()][solution[0]]; // Return to starting node
    return cost;
}

// Calculate the delta change for swapping two cities
int TabuSearch::computeSwapDelta(const std::vector<int>& solution, int i, int j) const {
    int size = solution.size();
    int prevI = (i - 1 + size) % size, nextI = (i + 1) % size;
    int prevJ = (j - 1 + size) % size, nextJ = (j + 1) % size;

    int delta = 0;
    if (prevI != j && nextI != j) {
        delta -= distanceMatrix[solution[prevI]][solution[i]] + distanceMatrix[solution[i]][solution[nextI]];
        delta += distanceMatrix[solution[prevI]][solution[j]] + distanceMatrix[solution[j]][solution[nextI]];

        delta -= distanceMatrix[solution[prevJ]][solution[j]] + distanceMatrix[solution[j]][solution[nextJ]];
        delta += distanceMatrix[solution[prevJ]][solution[i]] + distanceMatrix[solution[i]][solution[nextJ]];
    } else {
        delta -= distanceMatrix[solution[prevI]][solution[i]] + distanceMatrix[solution[i]][solution[j]] + distanceMatrix[solution[j]][solution[nextJ]];
        delta += distanceMatrix[solution[prevI]][solution[j]] + distanceMatrix[solution[j]][solution[i]] + distanceMatrix[solution[i]][solution[nextJ]];
    }
    return delta;
}

// Generate random permutation
std::vector<int> TabuSearch::generateRandomSolution(int size) const {
    std::vector<int> permutation(size);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), std::mt19937(std::random_device{}()));
    return permutation;
}

// Solve using Tabu Search
void TabuSearch::solve() {
    const int size = distanceMatrix.size();
    std::vector<std::vector<int>> tabuMatrix(size, std::vector<int>(size, 0));

    currentSolution = generateRandomSolution(size);
    currentSolutionCost = computeSolutionCost(currentSolution);
    optimalSolution = currentSolution;
    optimalCost = computeSolutionCost(currentSolution); 

    auto startTime = std::chrono::high_resolution_clock::now();

    while (true) {
        int bestNeighborCost = std::numeric_limits<int>::max();
        std::vector<int> bestNeighbor = currentSolution;
        int swapX = -1, swapY = -1;

        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int delta = computeSwapDelta(currentSolution, i, j);
                int neighborCost = currentSolutionCost + delta;

                if (neighborCost < bestNeighborCost && tabuMatrix[i][j] <= iterationCounter) {
                    bestNeighborCost = neighborCost;
                    bestNeighbor = currentSolution;
                    swapX = i;
                    swapY = j;
                }
            }
        }

        if (swapX != -1 && swapY != -1) {
            std::swap(bestNeighbor[swapX], bestNeighbor[swapY]);
            tabuMatrix[swapX][swapY] = iterationCounter + size;
        } else {
            bestNeighbor = generateRandomSolution(size); 
        }

        currentSolution = bestNeighbor;
        currentSolutionCost = computeSolutionCost(currentSolution); 

        if (currentSolutionCost < optimalCost) {
            optimalCost = currentSolutionCost;
            optimalSolution = currentSolution;
            bestSolutionTimestamp = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
        }

        iterationCounter++;

        auto currentTime = std::chrono::high_resolution_clock::now();
        double elapsedTime = std::chrono::duration<double>(currentTime - startTime).count();
        if (elapsedTime >= maxDuration) break;
    }
}

// Get the best tour
std::vector<int> TabuSearch::getOptimalSolution() const {
    return optimalSolution;
}

// Get the best cost
int TabuSearch::getOptimalCost() const {
    return optimalCost;
}

// Get the time when the best solution was found
double TabuSearch::getBestTourTimestamp() const {
    return bestSolutionTimestamp;
}

// Save the results to a file
void TabuSearch::saveResultsToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    if (!outFile) {
        throw std::runtime_error("Error: Unable to open file for writing.");
    }

    outFile << optimalSolution.size() << std::endl;
    for (int city : optimalSolution) {
        outFile << city << " ";
    }
    outFile << std::endl;
    outFile.close();
}

