#include <iostream>
#include "Option.h"


void mainMenu();
void printMainMenu();
Option validateInput(std::string str_input);
int convertStringToInt(std::string input);
void buttonPress();
void clearTerminal();


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

    buttonPress();
    clearTerminal();
  } while(option_input != Option::EXIT);

}

void printMainMenu() {
  std::cout << "Aplication solving ATSP Problem using Tabu Search and Simulated Annealing problem\n";  
  std::cout << "1. Load datat set\n";
  std::cout << "2. Set stop criterion\n";
  std::cout << "3. Solve problem using Brute Force Algorithm\n";
  std::cout << "4. Define neighbors for Tabu Search\n";
  std::cout << "5. Solve problem using Tabu Search Algorihtm\n";
  std::cout << "6. Set temperatur change factor\n";
  std::cout << "7. Solve problem using Simulated Annealing\n";
  std::cout << "8. Save results to file\n";
  std::cout << "9. Load cost tabels\n"; 
  std::cout << "10. Exit\n";
  return; 
}

Option validateInput(std::string str_input) {
  int input = convertStringToInt(str_input);
  switch (input) {
    case 1: { return Option::LOAD_DATA; }
    case 2: { return Option::STOP_CRITERION; }
    case 3: { return Option::BRUTE_FORCE; }
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
