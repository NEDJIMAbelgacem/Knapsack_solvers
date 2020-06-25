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

#include "UnboundedKnapsackSolverHeur.h"
#include "Utils.h"

std::tuple<double, double, std::vector<int>> benchmark_dataset(std::string dataset_file, std::string func) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::vector<double> items_weight, items_values;
    double sack_weight;
    read_ukp_datset(dataset_file, items_weight, items_values, sack_weight);
    std::vector<int> solution;

    std::cout << "Sack size : " << sack_weight << std::endl;

    if (func == "value-ordered") {
        auto heur_function = [&](int a, int b) {
            return items_values[a] > items_values[b];
        };
        start = std::chrono::system_clock::now();
        UnboundedKnapsackSolverHeur solver(items_weight, items_values, heur_function);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        solution = solver.solve(sack_weight);
    } else if (func == "density-ordered") {
        auto heur_function = [&](int a, int b) {
            return items_values[a] / items_weight[a] > items_values[b] / items_weight[b];
        };
        start = std::chrono::system_clock::now();
        UnboundedKnapsackSolverHeur solver(items_weight, items_values, heur_function);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        solution = solver.solve(sack_weight);
    }

    solution = convertToNsolution(solution, items_weight.size());

    double total_profit = calculate_total_values(solution, items_weight, items_values);
    double total_weight = calculate_total_weight(solution, items_weight, items_values);
    std::cout << "Total weight : " << total_weight << std::endl;
    double time_taken = elapsed_seconds.count();
    return std::make_tuple(total_profit, time_taken, solution);
}

int main(int argc, char** argv) {
    srand(1);
    std::string method = std::string(argv[1]);
    std::cout << "Heuristic: " << method << std::endl;
    bool print_solution = std::stoi(std::string(argv[2]));
    for (int i = 3; i < argc; ++i) {
        auto [profit, time, solution] = benchmark_dataset(std::string(argv[i]), method);
        std::cout << "Dataset: " << argv[i] << std::endl;
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
