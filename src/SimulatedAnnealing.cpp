#include "../headers/SimulatedAnnealing.h"
#include "../headers/GreedyAlgorithm.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>
#include <limits>

/**
 * Constructor for SimulatedAnnealing.
 * Initializes the algorithm with the given graph, cooling factor, and maximum time.
 * @param graph - Adjacency matrix representing distances between nodes.
 * @param coolingFactor - The cooling rate for the temperature decrease.
 * @param maxTime - The maximum time allowed for the algorithm to run.
 */
SimulatedAnnealing::SimulatedAnnealing(const std::vector<std::vector<int>>& graph, double coolingFactor, double maxTime)
    : graph(graph), coolingFactor(coolingFactor), maxTime(maxTime), bestCost(std::numeric_limits<int>::max()), bestSolutionTimestamp(0.0) {
    graphSize= graph.size();
}

/**
 * Solves the ATSP problem using Simulated Annealing.
 * Uses the Greedy Algorithm to generate an initial solution and then improves it using Simulated Annealing.
 */
void SimulatedAnnealing::solve() {

    GreedyAlgorithm* greedySolver = new GreedyAlgorithm(graph);
    greedySolver->solve();

    currentSolution = greedySolver->getBestTour();
    currentCost = greedySolver->getBestCost();

    runSimulatedAnnelingFor(currentSolution);
}

/**
 * Retrieves the best solution found during the search.
 * @return The best solution as a sequence of node indices.
 */
std::vector<int> SimulatedAnnealing::getBestSolution() const {
    return bestSolution;
}

/**
 * Retrieves the cost of the best solution found during the search.
 * @return The cost of the best solution.
 */
int SimulatedAnnealing::getBestCost() const {
    return bestCost;
}

/**
 * Retrieves the timestamp when the best solution was found.
 * @return The timestamp in seconds since the start of the algorithm.
 */
double SimulatedAnnealing::getBestSolutionTimestamp() const {
    return bestSolutionTimestamp;
}

/**
 * Saves the results (best solution and its cost) to a specified file.
 * @param fileName - The name of the file to save the results to.
 */
void SimulatedAnnealing::saveResultsToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName, std::ios::out);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << " for writing.\n";
        return;
    }

    outFile << bestSolution.size() << "\n";
    for (int city : bestSolution) {
        outFile << city << " ";
    }
    outFile << "\n";

    outFile.close();
}

/**
 * Calculates the total cost of a given solution.
 * @param solution - The current solution represented as a sequence of node indices.
 * @param adjacencyMatrix - The graph's adjacency matrix.
 * @param size - The number of nodes in the graph.
 * @return The total cost of the solution.
 */
int SimulatedAnnealing::calculateCost(const std::vector<int> &solution, std::vector<std::vector<int>> adjacencyMatrix, int size) {
    int cost = 0;

    for (int i = 0; i < size - 1; i++) {
        cost += adjacencyMatrix[solution[i]][solution[i + 1]];
    }
    cost += adjacencyMatrix[solution[size - 1]][solution[0]]; // Powrót do startu
    return cost;
}

/**
 * Executes the Simulated Annealing algorithm for a given initial solution.
 * @param initialSolution - The starting solution for the algorithm.
 */
void SimulatedAnnealing::runSimulatedAnnelingFor(std::vector<int> initialSolution) {

    std::vector<int> currentSolution;
    std::vector<int> newSolution;
    int currentCost;
    int newSolutionCost;
    double time;

    auto startTime = std::chrono::high_resolution_clock::now();

    currentSolution = initialSolution;
    currentCost = calculateCost(currentSolution, graph, graphSize);
    this->bestSolution = currentSolution;
    this->bestCost = currentCost;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randrand(1, graphSize- 2);

    std::vector<int> startedCosts;
    int newCost;
    int avg = 0;
    int firstSwapIndex;
    int secondSwapIndex;

    for(int i = 0; i < 50; i++){
        newSolution = currentSolution;

        do {
            firstSwapIndex = randrand(gen);
            secondSwapIndex = randrand(gen);
        } while (firstSwapIndex == secondSwapIndex);

        std::swap(newSolution[firstSwapIndex], newSolution[secondSwapIndex]); 
        newSolutionCost = calculateCost(newSolution, graph, graphSize) - currentCost;
        avg += newSolutionCost;
    }

    double temp = -(avg/50) / log(0.98);
    std::cout << "Initial temperature: " << temp << std::endl;

    while (true) {

        double expo;
        do {
            newSolution = currentSolution;

            do {
                firstSwapIndex = randrand(gen);
                secondSwapIndex = randrand(gen);
            } while (firstSwapIndex == secondSwapIndex);

            int vertex= newSolution[firstSwapIndex];
            newSolution.erase(newSolution.begin() + firstSwapIndex); // Usuń wierzchołek
            newSolution.insert(newSolution.begin() + secondSwapIndex, vertex); // Wstaw w nowe miejsce

            if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count() >= maxTime) {
                std::cout << "Final Temperature (Tk): " << temp << std::endl;
                std::cout << "exp(-1/Tk): " << std::exp(-1.0/temp) << std::endl;
                this->bestSolution = bestSolution;
                this->bestCost = bestCost;
                return;
            }

            newCost = calculateCost(newSolution, graph, graphSize);
            time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
            temp *= coolingFactor;
            expo = exp((currentCost - newCost) / temp);

        } while(newCost >= currentCost || expo <= 0.9);

        if (newCost < bestCost) {
            bestSolution = newSolution;
            bestCost = newCost;
            bestSolutionTimestamp = time;
        }

        currentSolution = newSolution;
    }
}
