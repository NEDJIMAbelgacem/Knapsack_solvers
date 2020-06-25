#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <chrono>

#include "KnapsackSolverGA.h"
#include "Utils.h"

int main(int argc, char** argv) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    srand(0);
    std::vector<double> items_weight, items_values;
    int taille_instance = std::stoi(std::string(argv[1]));
    double sack_weight = std::stod(std::string(argv[2]));
    int population_size = std::stoi(std::string(argv[3]));
    int generations_count = std::stoi(std::string(argv[4]));

    if (std::string(argv[argc - 1]) == "random") generate_random_instance(taille_instance, items_weight, items_values, 10, 80);
    else read_ukp_datset(std::string(argv[argc - 1]), items_weight, items_values, sack_weight);
    sack_weight = std::stoi(std::string(argv[2]));

    KnapsackSolverGA solver(items_weight, items_values);
    solver.population_size = population_size;
    solver.generations_count = generations_count;

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_weight);
    end = std::chrono::system_clock::now();

    std::cout << solver.fittness_history.size() << "\n";
    for (double d : solver.fittness_history) std::cout << d << "\n";

    std::cout << solution.size() << "\n";
    for (int i : solution) std::cout << i << "\n";

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cerr << elapsed_seconds.count() << std::endl;
    std::cout << elapsed_seconds.count() << std::endl;
}
