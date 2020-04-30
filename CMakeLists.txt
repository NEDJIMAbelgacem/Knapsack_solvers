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

add_executable(proj_optim
    main.cpp
    sources/KnapsackSolverDP.cpp
    sources/KnapsackSolverBnB.cpp
    sources/UnboundedKnapsackSolverBnB.cpp
    sources/UnboundedKnapsackSolverDP.cpp
)