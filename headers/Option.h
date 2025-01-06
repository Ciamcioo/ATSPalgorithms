/**
 * Enum class representing the available menu options in the program.
 * Each option corresponds to a specific functionality or action that can be performed by the user.
 */
enum class Option { 
    LOAD_DATA,               ///< Load problem data or cost tables from a file or other sources.
    STOP_CRITERION,          ///< Set the stop criterion for the algorithms (e.g., time limit or iteration count).
    GREEDY_ALGORITHM,        ///< Run the Greedy Algorithm to solve the problem.
    RUN_TABU_SEARCH,         ///< Run the Tabu Search algorithm to solve the problem.
    SET_TEMP_CHANGE_FACTOR,  ///< Set the cooling factor for the Simulated Annealing algorithm.
    RUN_SIMULATED_ANNEALING, ///< Run the Simulated Annealing algorithm to solve the problem.
    SAVE_TO_FILE,            ///< Save the results of the computation to a file.
    LOAD_COST_TABELS,        ///< Load pre-defined cost tables for testing or benchmarking.
    EXIT,                    ///< Exit the program.
    INVALID_INPUT            ///< Represents an invalid or unrecognized input option.
};

