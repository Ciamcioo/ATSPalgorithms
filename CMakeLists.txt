cmake_minimum_required(VERSION 3.5.0)
project(ATSP_2 VERSION 0.1.0 LANGUAGES C CXX)

# Add the include direcotry for header file
include_directories(headers)

add_executable(ATSP_2 src/main.cpp src/GreedyAlgorithm.cpp src/TabuSearch.cpp src/SimulatedAnnealing.cpp)

