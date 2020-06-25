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
#include <tuple>

#include "KnapsackSolverHybrid.h"
#include "Utils.h"

std::tuple<double, double, std::vector<int>> benchmark_dataset(std::string dataset_file, int GA_population_size, int GA_generations_count, int SA_iterations) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<double> items_weight, items_values;
    double sack_weight;
    read_ukp_datset(dataset_file, items_weight, items_values, sack_weight);

    KnapsackSolverHybrid solver(items_weight, items_values);
    solver.generations_count = GA_generations_count;
    solver.population_size = GA_population_size;
    solver.max_SA_iterations_count = SA_iterations;

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_weight);
    end = std::chrono::system_clock::now();
    double total_profit = calculate_total_values(solution, items_weight, items_values );
    std::chrono::duration<double> elapsed_seconds = end - start;
    double time_taken = elapsed_seconds.count();
    return std::make_tuple(total_profit, time_taken, solution);
}

int main(int argc, char** argv) {
    std::cout << "Hybrid algorithm" << std::endl;
    srand(1);
    int GA_population_size = std::stoi(std::string(argv[1]));
    int GA_generations_count = std::stoi(std::string(argv[2]));
    int SA_iterations = std::stoi(std::string(argv[3]));
    bool print_solution = std::stoi(std::string(argv[4]));
    for (int i = 5; i < argc; ++i) {
        auto [profit, time, solution] = benchmark_dataset(std::string(argv[i]), GA_population_size, GA_generations_count,  SA_iterations);
        std::cout << "Profit: " << profit << std::endl;
        std::cout << "Time: " << time << std::endl;
        if (print_solution) {
            std::cout << solution.size() << std::endl;
            for (int i : solution) {
                std::cout << i << std::endl;
            }
        }
    }
}
