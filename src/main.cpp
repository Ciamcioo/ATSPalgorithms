/**
 * Main Application for Solving ATSP
 * ----------------------------------
 * This application solves the Asymmetric Traveling Salesman Problem (ATSP) using
 * three algorithms: Greedy Algorithm, Tabu Search, and Simulated Annealing. Users
 * can interact via a menu interface to load data, configure parameters, execute
 * algorithms, and save results.
 */


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "../headers/Option.h"
#include "../headers/TabuSearch.h"
#include "../headers/GreedyAlgorithm.h"
#include "../headers/SimulatedAnnealing.h"



/**
 * Global Variables
 * ----------------
 * distanceMatrix : A 2D vector storing the adjacency matrix for the ATSP.
 * maxRunTime : Maximum computation time for algorithms in seconds (default: 60 seconds).
 * temperatureChangeFactor : Cooling rate for Simulated Annealing (default: 0.85).
 * greedySolver : Pointer to an instance of the GreedyAlgorithm class.
 * tabuSolver : Pointer to an instance of the TabuSearch class.
 * simulatedAnnealingSolver : Pointer to an instance of the SimulatedAnnealing class.
 * resultsFilePath : Default path to save results ("results.txt").
 */
std::vector<std::vector<int>> distanceMatrix;
long maxRunTime = 60L; // Default run time in seconds
float temperatureChangeFactor = 0.85;

GreedyAlgorithm* greedySolver = nullptr;
TabuSearch* tabuSolver = nullptr;
SimulatedAnnealing* simulatedAnnealingSolver = nullptr;

std::string resultsFilePath = "/home/ciamcio/workspace/cppPrograming/ATSPalgorithms/results.txt";


// Function Declarations
void displayMainMenu();
Option validateInput(const std::string& input);
int convertStringToInt(const std::string& input);
void handleMenuOption(Option selectedOption);
void pressEnterToContinue();
void clearScreen();

std::vector<std::vector<int>> loadMatrixFromFile(const std::string& path);

void setMaxRunTime(long seconds);
void setTemperatureChangeFactor(float factor);
void loadCostTable();

/**
 * Main Function
 * -------------
 * Loops indefinitely, displaying a menu to the user. Handles user input
 * and invokes appropriate methods based on menu selection.
 */
int main() {
    while (true) {
        displayMainMenu();
        std::string inputString;
        std::getline(std::cin, inputString);
        Option selectedOption = validateInput(inputString);
        if (selectedOption == Option::EXIT) break;
        handleMenuOption(selectedOption);
        pressEnterToContinue();
        clearScreen();
    }
    return 0;
}

/**
 * Displays the main menu options to the console.
 */
void displayMainMenu() {
    std::cout << "Application solving the ATSP problem using Tabu Search and Simulated Annealing\n";
    std::cout << "1. Load dataset\n";
    std::cout << "2. Set maximum calculation time (stop criterion)\n";
    std::cout << "3. Solve problem using Greedy Algorithm\n";
    std::cout << "4. Solve problem using Tabu Search\n";
    std::cout << "5. Set temperature change factor for Simulated Annealing\n";
    std::cout << "6. Solve problem using Simulated Annealing\n";
    std::cout << "7. Save results to file\n";
    std::cout << "8. Load cost tables\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter the number corresponding to your choice: ";
}

/**
 * Converts user input into an Option enum. Returns Option::INVALID_INPUT for invalid entries.
 * @param input - The user input as a string.
 * @return The corresponding Option enum value.
 */
Option validateInput(const std::string& input) {
    int option = convertStringToInt(input);
    switch (option) {
        case 1: return Option::LOAD_DATA;
        case 2: return Option::STOP_CRITERION;
        case 3: return Option::GREEDY_ALGORITHM;
        case 4: return Option::RUN_TABU_SEARCH;
        case 5: return Option::SET_TEMP_CHANGE_FACTOR;
        case 6: return Option::RUN_SIMULATED_ANNEALING;
        case 7: return Option::SAVE_TO_FILE;
        case 8: return Option::LOAD_COST_TABELS;
        case 0: return Option::EXIT;
        default: return Option::INVALID_INPUT;
    }
}

/**
 * Executes the functionality corresponding to the user's menu choice.
 * @param selectedOption - The selected menu option.
 */
void handleMenuOption(Option selectedOption) {
    switch (selectedOption) {

        case Option::LOAD_DATA: {
            std::string filePath;
            std::cout << "Enter the path to the data file: ";
            std::cin >> filePath;
            try {
                distanceMatrix = loadMatrixFromFile(filePath);
                std::cout << "Data loaded successfully.\n";
                std::cout << "Matrix size: " << distanceMatrix.size() << " x " << distanceMatrix.size() << "\n";
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }

        case Option::STOP_CRITERION: {
            std::string input;
            std::cout << "Enter the maximum calculation time (in seconds): ";
            std::cin >> input;
            int seconds = convertStringToInt(input);
            setMaxRunTime(seconds);
            std::cout << "Stop criterion set to " << maxRunTime << " seconds.\n";
            break;
        }

        case Option::GREEDY_ALGORITHM: {
            if (distanceMatrix.empty()) {
                std::cerr << "Error: Distance matrix is empty.\n";
                break;
            }
            if (greedySolver) delete greedySolver;
            greedySolver = new GreedyAlgorithm(distanceMatrix);
            greedySolver->solve();
            std::cout << "Greedy Algorithm Results:\n";
            std::cout << "Number of vertices: " << greedySolver->getMatrixSize() << "\n";
            std::cout << "Best cost: " << greedySolver->getBestCost() << "\n";
            std::cout << "Best tour: ";
            for (int city : greedySolver->getBestTour()) {
                std::cout << city << " ";
            }
            std::cout << std::endl;
            break;
        }

        case Option::RUN_TABU_SEARCH: {
            if (distanceMatrix.empty()) {
                std::cerr << "Error: Distance matrix is empty.\n";
                break;
            }
            if (tabuSolver) delete tabuSolver;
            tabuSolver = new TabuSearch(distanceMatrix, 2, maxRunTime);
            tabuSolver->solve();
            std::cout << "Tabu Search Results:\n";
            std::cout << "Best cost: " << tabuSolver->getOptimalCost() << "\n";
            std::cout << "Best tour: ";
            for (int city : tabuSolver->getOptimalSolution()) {
                std::cout << city << " ";
            }
            std::cout << std::endl;
            std::cout << "Tiem stamp when found: " << tabuSolver->getBestTourTimestamp();
            break;
        }

        case Option::SET_TEMP_CHANGE_FACTOR: {
            float factor;
            std::cout << "Enter temperature change factor (0.8 - 0.99 recommended): ";
            std::cin >> factor;
            setTemperatureChangeFactor(factor);
            std::cout << "Temperature change factor set to " << temperatureChangeFactor << ".\n";
            break;
        }

        case Option::RUN_SIMULATED_ANNEALING: {
            if (distanceMatrix.empty()) {
                std::cerr << "Error: Distance matrix is empty.\n";
                break;
            }
            if (simulatedAnnealingSolver) delete simulatedAnnealingSolver;
            simulatedAnnealingSolver = new SimulatedAnnealing(distanceMatrix, temperatureChangeFactor, maxRunTime);
            simulatedAnnealingSolver->solve();
            std::cout << "Best cost: " << simulatedAnnealingSolver->getBestCost() << "\n";
            std::cout << "Best tour: ";
            for (int city : simulatedAnnealingSolver->getBestSolution()) {
                std::cout << city << " ";
            }
            std::cout << std::endl;
            std::cout << "Tiem stamp when found: " << simulatedAnnealingSolver->getBestSolutionTimestamp() << std::endl; 
            break;
        }

        case Option::SAVE_TO_FILE: {
            if (greedySolver) greedySolver->saveResultToFile(resultsFilePath);
            if (tabuSolver) tabuSolver->saveResultsToFile(resultsFilePath);
            std::cout << "Results saved to " << resultsFilePath << ".\n";
            break;
        }

        case Option::LOAD_COST_TABELS: {
            loadCostTable();
            break;
        }

        case Option::INVALID_INPUT:
            std::cerr << "Invalid input. Please try again.\n";
            break;

        default:
            break;
    }
}

/**
 * Loads the adjacency matrix from a specified file. The file must follow the ATSP format.
 * @param filePath - The path to the file containing the matrix data.
 * @return The loaded matrix as a 2D vector.
 */
std::vector<std::vector<int>> loadMatrixFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filePath);
    }

    std::string line;
    std::vector<int> weights;
    int dimension = 0;

    while (std::getline(file, line)) {
        if (line.find("DIMENSION") != std::string::npos) {
            dimension = std::stoi(line.substr(line.find(":") + 1));
        } else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            break;
        }
    }

    while (std::getline(file, line)) {
        if (line == "EOF") break;
        std::istringstream iss(line);
        int weight;
        while (iss >> weight) {
            weights.push_back(weight);
        }
    }

    std::vector<std::vector<int>> matrix(dimension, std::vector<int>(dimension));
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            matrix[i][j] = weights[i * dimension + j];
        }
    }
    return matrix;
}

/**
 * Converts a string to an integer. Returns 0 for invalid inputs.
 * @param input - The string input to convert.
 * @return The integer value of the input.
 */
int convertStringToInt(const std::string& input) {
    try {
        return std::stoi(input);
    } catch (...) {
        return 0;
    }
}

/**
 * Loads a cost table from the results file and calculates the tour cost.
 * Ensures the data matches the loaded distance matrix.
 */
void loadCostTable() {
    if (distanceMatrix.empty()) {
        std::cerr << "Error: Distance matrix is not loaded. Please load a dataset first.\n";
        return;
    }

    std::ifstream inFile(resultsFilePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << resultsFilePath << " for reading.\n";
        return;
    }

    std::string line;
    int numberOfVertices = 0;
    std::vector<int> tour;

    try {
        if (std::getline(inFile, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); 
            numberOfVertices = std::stoi(line);
        } else {
            throw std::runtime_error("Error: File format is invalid. Missing number of vertices.");
        }

        if (std::getline(inFile, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::istringstream iss(line);
            int vertex;
            while (iss >> vertex) {
                tour.push_back(vertex);
            }
        } else {
            throw std::runtime_error("Error: File format is invalid. Missing tour information.");
        }

        inFile.close();

        if (numberOfVertices != static_cast<int>(distanceMatrix.size())) {
            throw std::runtime_error("Error: Number of vertices in the file does not match the loaded distance matrix.");
        }
        if (tour.empty()) {
            throw std::runtime_error("Error: Tour information is missing or invalid in the file.");
        }

        int totalCost = 0;
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            if (tour[i] >= numberOfVertices || tour[i + 1] >= numberOfVertices) {
                throw std::runtime_error("Error: Invalid vertex in the tour.");
            }
            totalCost += distanceMatrix[tour[i]][tour[i + 1]];
        }
        totalCost += distanceMatrix[tour[distanceMatrix.size()-1]][tour[0]];

        std::cout << "Loaded Tour Cost: " << totalCost << "\n";
        std::cout << "Tour: ";
        for (int vertex : tour) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Sets the maximum runtime for algorithms.
 * Ensures the value is within the range [1, 36000].
 * @param seconds - Maximum runtime in seconds.
 */
void setMaxRunTime(long seconds) {
    maxRunTime = (seconds > 0 && seconds <= 36000) ? seconds : 60;
}

/**
 * Sets the cooling factor for Simulated Annealing.
 * Ensures the value is within the range [0.8, 0.99].
 * @param factor - Cooling factor.
 */
void setTemperatureChangeFactor(float factor) {
    temperatureChangeFactor = (factor >= 0.8 && factor < 1) ? factor : 0.85;
}

/**
 * Waits for the user to press "Enter" to continue.
 */
void pressEnterToContinue() {
    std::cin.ignore();
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();
}

/**
 * Clears the console window. Works across platforms.
 */
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

