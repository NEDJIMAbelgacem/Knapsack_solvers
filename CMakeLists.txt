cmake_minimum_required(VERSION 3.0.0)
project(proj_optim VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(
  include/
)

set(SOLVERS 
    sources/KnapsackSolverDP.cpp
    sources/KnapsackSolverBnB.cpp
    sources/UnboundedKnapsackSolverBnB.cpp
    sources/UnboundedKnapsackSolverDP.cpp
    sources/KnapsackSolverSA.cpp
    sources/KnapsackSolverGA.cpp
    sources/KnapsackSolverHybrid.cpp
    sources/Utils.cpp
)

add_executable(branch_and_bound
    Methods/BranchNBound.cpp
    ${SOLVERS}
)

add_executable(dynamic_programming
    Methods/DynamicProgramming.cpp
    ${SOLVERS}
)

add_executable(heuristics
    Methods/Heuristics.cpp
    ${SOLVERS}
)

add_executable(genetic_algorithm
    Methods/GeneticAlgorithm.cpp
    ${SOLVERS}
)

add_executable(simulated_annealing
    Methods/SimulatedAnnealing.cpp
    ${SOLVERS}
)

add_executable(hybrid_algorithm
    Methods/HybridAlgorithm.cpp
    ${SOLVERS}
)

add_executable(benchmark_branch_and_bound
    Methods_benchmark/BranchNBound.cpp
    ${SOLVERS}
)

add_executable(benchmark_dynamic_programming
    Methods_benchmark/DynamicProgramming.cpp
    ${SOLVERS}
)

add_executable(benchmark_heuristics
    Methods_benchmark/Heuristics.cpp
    ${SOLVERS}
)

add_executable(benchmark_genetic_algorithm
    Methods_benchmark/GeneticAlgorithm.cpp
    ${SOLVERS}
)

add_executable(benchmark_simulated_annealing
    Methods_benchmark/SimulatedAnnealing.cpp
    ${SOLVERS}
)

add_executable(benchmark_hybrid_algorithm
    Methods_benchmark/HybridAlgorithm.cpp
    ${SOLVERS}
)