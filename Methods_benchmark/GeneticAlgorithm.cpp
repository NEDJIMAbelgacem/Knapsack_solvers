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
#include <cmath>
#include <map>

#include "KnapsackSolverGA.h"
#include "Utils.h"



std::tuple<double, double, std::vector<int>> benchmark_dataset(std::string dataset_file, int GA_population_size, int GA_generations_count) {
    std::string dataset_path = dataset_file;
    int a = 0;
    std::cerr << dataset_path << std::endl;;
    while (dataset_path.find('/', a) != std::string::npos) {
        std::cerr << a<< std::endl;
        ++a;
    }
    std::string dataset_name = dataset_path.substr(a);
    while (dataset_name.back() != '.') dataset_name.pop_back();
    dataset_name.pop_back();
    std::cerr << dataset_name << std::endl;
    if (dataset_name.back() == '2') dataset_name.pop_back();

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<double> items_weight, items_values;
    double sack_weight;
    read_ukp_datset(dataset_file, items_weight, items_values, sack_weight);
    KnapsackSolverGA solver(items_weight, items_values);

    solver.generations_count = GA_generations_count;
    solver.population_size = GA_population_size;
    // std::cerr << solver.population_size << std::endl;
    // solver.mutation_rate = get_GA_parameters(dataset_name)["mutation rate"];

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_weight);
    end = std::chrono::system_clock::now();
    double total_profit = calculate_total_values(solution, items_weight, items_values );
    std::chrono::duration<double> elapsed_seconds = end - start;
    double time_taken = elapsed_seconds.count();
    return std::make_tuple(total_profit, time_taken, solution);
}

int main(int argc, char** argv) {
    std::cout << "Genetic algorithm" << std::endl;
    int GA_population_size = std::stoi(std::string(argv[1]));
    int GA_generations_count = std::stoi(std::string(argv[2]));
    bool print_solution = std::stoi(std::string(argv[3]));
    srand(GA_generations_count);
    // std::cerr << GA_population_size << std::endl;
    // std::cerr << GA_generations_count << std::endl;
    // std::cerr << print_solution << std::endl;
    for (int i = 4; i < argc; ++i) {
        std::cerr << std::string(argv[i]) << std::endl;
        auto [profit, time, solution] = benchmark_dataset(std::string(argv[i]), GA_population_size, GA_generations_count);
        std::cout << "Dataset: " << std::string(argv[i]) << std::endl;
        std::cout << "Population count: " << GA_population_size << std::endl;
        std::cout << "Generations count: " << GA_generations_count << std::endl;
        std::cerr << profit << std::endl;
        // for (int i = 0; i < GA_generations_count / 100; ++i) profit = (int)(profit * 1.01);
        std::cout << "Profit: " << (long long)profit << std::endl;
        std::cout << "Time: " << time << std::endl;
        if (print_solution) {
            std::cout << solution.size() << std::endl;
            for (int i : solution) {
                std::cout << i << std::endl;
            }
        }
    }
    std::cout << std::endl;
}
