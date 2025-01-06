# ATSP Solver

This project implements an application to solve the **Asymmetric Traveling Salesman Problem (ATSP)** using three algorithms:
- **Greedy Algorithm**
- **Tabu Search**
- **Simulated Annealing**

The program provides a menu-based interface for loading datasets, configuring parameters, executing algorithms, and saving results.

## Features

1. **Menu-Driven Interface**:
   - Load datasets and cost tables.
   - Configure algorithm parameters like maximum runtime and cooling factor.
   - Run algorithms and save results to a file.

2. **Implemented Algorithms**:
   - **Greedy Algorithm**: Constructs a tour by repeatedly selecting the nearest unvisited city.
   - **Tabu Search**: Utilizes a tabu list to avoid revisiting solutions and explores neighbors to minimize costs.
   - **Simulated Annealing**: Starts with a greedy solution and iteratively improves it by probabilistically accepting worse solutions to escape local minima.

3. **Output Features**:
   - Displays the best solution and cost for each algorithm.
   - Saves results to a specified file.

## Directory Structure

```
.
├── headers
│   ├── GreedyAlgorithm.h
│   ├── TabuSearch.h
│   ├── SimulatedAnnealing.h
│   ├── Option.h
├── src
│   ├── main.cpp
│   ├── GreedyAlgorithm.cpp
│   ├── TabuSearch.cpp
│   ├── SimulatedAnnealing.cpp
├── CMakeLists.txt
```

## Installation and Compilation

1. Ensure you have **CMake** (minimum version 3.5.0) and a compatible C++ compiler installed.
2. Clone the repository and navigate to the project directory.
3. Build the project using the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

This will generate an executable named `ATSP_2` in the `build` directory.

## Usage

Run the program:

```bash
./ATSP_2
```

Follow the on-screen menu to:
- Load datasets in ATSP format.
- Configure runtime parameters.
- Run any of the three algorithms.
- Save results to a file.

### Dataset Format
The input file should adhere to the following structure:
- Include `DIMENSION` (number of nodes) and `EDGE_WEIGHT_SECTION`.
- Provide the adjacency matrix row by row.
- Terminate with `EOF`.

Example:
```
DIMENSION: 5
EDGE_WEIGHT_SECTION
0 29 20 21 16
29 0 15 17 28
20 15 0 18 23
21 17 18 0 11
16 28 23 11 0
EOF
```

## Algorithms Details

### Greedy Algorithm
- Iterates through all cities as starting points.
- Builds a tour by selecting the nearest unvisited city.
- Returns the best tour among all starting points.

### Tabu Search
- Maintains a tabu list to avoid revisiting recently explored solutions.
- Explores neighbors by swapping city pairs.
- Diversifies the search to escape local minima.

### Simulated Annealing
- Starts with a greedy solution.
- Iteratively perturbs the solution, accepting worse solutions with a probability that decreases over time.
- Balances exploration and exploitation to escape local minima.

## Configuration Options
- **Maximum Runtime**: Set the time limit (in seconds) for algorithms.
- **Cooling Factor**: Adjust the cooling rate for Simulated Annealing (recommended: 0.8 - 0.99).

## Example Output
```
Application solving the ATSP problem using Tabu Search and Simulated Annealing
1. Load dataset
2. Set maximum calculation time (stop criterion)
3. Solve problem using Greedy Algorithm
4. Solve problem using Tabu Search
5. Set temperature change factor for Simulated Annealing
6. Solve problem using Simulated Annealing
7. Save results to file
8. Load cost tables
0. Exit
Enter the number corresponding to your choice: 
```

## Contact
If you have any questions, feedback, or issues, feel free to reach out:
- **Email**: [jakub.maciocha@gmail.com](mailto:your_email@example.com)
- **GitHub**: [Cimacioo](https://github.com/Ciamcioo)

## License
This project is licensed under the MIT License. See the LICENSE file for details.

