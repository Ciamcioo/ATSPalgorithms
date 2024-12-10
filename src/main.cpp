#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "Option.h"
#include "Neighbors.h"


void mainMenu();
void printMainMenu();
Option validateInput(std::string str_input);
int convertStringToInt(std::string input);
void buttonPress();
void clearTerminal();
void performAction(Option option_input);
std::vector<std::vector<int>> loadMatrixFromFile(std::string path);
std::string trim(const std::string& str);
void setMaxTimeRun(int minutes);
void setNeightborChoosingSystem(std::string input);
void setTemperatureChangeFactor(float tmp);

std::vector<std::vector<int>> matrix;
int  max_run_time_minutes = 5;
Neighbors neighbors_chosing_system = Neighbors::RANDOM;
float temp_change_factor = 0.85;


int main(int, char**) {
  mainMenu();
}    

void mainMenu() {
  std::string str_input;
  Option option_input;

  do {
    printMainMenu();
    std::getline(std::cin, str_input);
    option_input = validateInput(str_input);
    performAction(option_input);
    buttonPress();
    clearTerminal();
  } while(option_input != Option::EXIT);

}

void printMainMenu() {
  std::cout << "Aplication solving ATSP Problem using Tabu Search and Simulated Annealing problem\n";  
  std::cout << "1. Load datat set\n";
  std::cout << "2. Set maximum time for calculation - stop criterion\n";
  std::cout << "3. Solve problem using Greedy Algorihtm\n";
  std::cout << "4. Define neighbors for Tabu Search\n";
  std::cout << "5. Solve problem using Tabu Search Algorihtm\n";
  std::cout << "6. Set temperatur change factor\n";
  std::cout << "7. Solve problem using Simulated Annealing\n";
  std::cout << "8. Save results to file\n";
  std::cout << "9. Load cost tabels\n"; 
  std::cout << "10. Exit\n";
  std::cout << "Provide number representing the menu option: ";
  return; 
}

Option validateInput(std::string str_input) {
  int input = convertStringToInt(str_input);
  switch (input) {
    case 1: { return Option::LOAD_DATA; }
    case 2: { return Option::STOP_CRITERION; }
    case 3: { return Option::GREEDY_ALGORITHM; }
    case 4: { return Option::DEFINE_NEIGHBOR_TS; }
    case 5: { return Option::RUN_TABU_SEARCH; }
    case 6: { return Option::SET_TEMP_CHANGE_FACTOR; }
    case 7: { return Option::RUN_SIMULATED_ANNEALING; }
    case 8: { return Option::SAVE_TO_FILE; }
    case 9: { return Option::LOAD_COST_TABELS; }
    case 10: { return Option::EXIT; }
    default: { return Option::INVALID_INPUT; }
  }
}

void performAction(Option option) {
  switch (option) {

      case Option::LOAD_DATA: { 
                                  std::string path_to_file = "";
                                  std::cout << "Provide path to file: ";
                                  std::cin >> path_to_file;
                                  matrix = loadMatrixFromFile(path_to_file);
                                  break;
                              }
       

     case Option::STOP_CRITERION: {
                                      std::string input = "";
                                      std::cout << "Provide number of minutes to set for stop criterion: ";
                                      std::cin >> input
                                      int minutes = convertStringToInt(input);
                                      setMaxTimeRun(minutes);
                                      break;
                                  }
      

     case Option::GREEDY_ALGORITHM: {
                                        break;
      
                                        
                                    }

    case Option::DEFINE_NEIGHBOR_TS: {
                                         std::string input = "";
                                         std::cout << "Define how you would like to choose neighbors in Tabu Search Algorithm\n";
                                         std::cout << "1. Randomly selecting neighbors\n"; 
                                         std::cout << "2. Greedy choice of neighbors\n";
                                         std::cout << "3. Probalistic neighbor selection\n";
                                         std::cout << "Provide number related to the option (if the number will not match any option, first option will be choose): ";
                                         std::cin >> input;
                                         neighbors_chosing_system  = setNeightborChoosingSystem(input);
                                         break;
                                      }

    case Option::RUN_TABU_SEARCH: {
                                      break;

                                  }
    
    case Option::SET_TEMP_CHANGE_FACTOR: {
                                             float tmp_temp_change_factor = 0.85;
                                             std::cout << "Specifie the temperature change factor (properly set temperatur change factor should be in range from 0.8 to 0.99)\n";
                                             std::cout << "WARNING! If provided number will be out of range <0.0, 1.0> it will be set to 0.85 by default\n";
                                             std::cout << "Provide temperature change factor: ";
                                             std::cin >> tmp_temp_change_factor;
                                             setTemperatureChangeFactor(tmp_temp_change_factor);
                                             break;
                                         }                                  

    case Option::RUN_SIMULATED_ANNEALING: {
                                              break;
                                          }
    case Option::SAVE_TO_FILE: {
                                   break;
                               }

    case Option::LOAD_COST_TABELS: {
                                       // TODO load matrix and then the path and based on that calculate the cost and print it out to the user

        
                                       break;
                                   }

    case Option::INVALID_INPUT: {
                                    std::cout << "Provided option is invalid" << std::endl;
                                    break;
                                }
                                    

    

  }
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

std::vector<std::vector<int>> loadMatrixFromFile(std::string filePath) { 
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string line;
    int dimension = 0;
    std::string edgeWeightFormat;
    std::vector<int> edgeWeights;
    bool readingWeights = false;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty()) continue;

        if (line.find("DIMENSION") != std::string::npos) {
            dimension = std::stoi(line.substr(line.find(":") + 1));
        } else if (line.find("EDGE_WEIGHT_FORMAT") != std::string::npos) {
            edgeWeightFormat = trim(line.substr(line.find(":") + 1));
            std::transform(edgeWeightFormat.begin(), edgeWeightFormat.end(), edgeWeightFormat.begin(), ::toupper); // Convert to uppercase
        } else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            readingWeights = true;
        } else if (line == "EOF") {
            break;
        } else if (readingWeights) {
            std::istringstream iss(line);
            int weight;
            while (iss >> weight) {
                edgeWeights.push_back(weight);
            }
        }
    }

    file.close();

    if (edgeWeightFormat == "FULL_MATRIX") {
        std::vector<std::vector<int>> weightMatrix(dimension, std::vector<int>(dimension));
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                weightMatrix[i][j] = edgeWeights[i * dimension + j];
            }
        }
        return weightMatrix;
    } else {
        throw std::runtime_error("Unsupported EDGE_WEIGHT_FORMAT: " + edgeWeightFormat);
    }
}

void setMaxTimeRun(int minutes) {
  if (minutes < 0 || minutes > 300) { 
    max_run_time_minutes= 5
  } else {
    max_run_time_minutes = minutes;
  }
}

void setNeightborChoosingSystem(std::string input) {
    int number = convertStringToInt(input);
    
    switch (number) {
        case 1: { neighbors_chosing_system = Neighbors::RANDOM; }
        case 2: { neighbors_chosing_system = Neighbors::GREEDY; }
        case 3: { neighbors_chosing_system = Neighbors::PROBALISTIC; }
        default: { neighbors_chosing_system = Neighbors::RANDOM; }
    }
}

void setTemperatureChangeFactor(float tmp) {
    if (tmp < 0.0 || tmp >= 1.0) {
        temp_change_factor = 0.85;
    } else {
        temp_change_factor = tmp_temp_change_factor;
    }
}


int convertStringToInt(std::string str_input) {
  int input = 0;
  try {
    input = std::stoi(str_input); 
  } catch (const std::invalid_argument& e) {
    std::cout << "Invalid input arguemnt\n";
  } catch(const std::out_of_range& e) {
    std::cout << "Argument out of range\n";
  } 
  return input;
}

void buttonPress() {
  std::cin.ignore();
  std::cout << "Press Enter to clear the terminal..." << std::endl;
  std::cin.get();
  return;
}

void clearTerminal() {
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
  return;
}
