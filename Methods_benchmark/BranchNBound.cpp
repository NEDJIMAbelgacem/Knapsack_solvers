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

#include "UnboundedKnapsackSolverBnB.h"
#include "Utils.h"

std::tuple<double, double, std::vector<int>> benchmark_dataset(int items_count, int sack_weight) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<double> items_weight, items_values;
    generate_random_instance(items_count, items_weight, items_values);

    UnboundedKnapsackSolverBnB solver(items_weight, items_values);

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_weight);
    end = std::chrono::system_clock::now();
    solution = convertToNsolution(solution, items_weight.size());
    double total_profit = calculate_total_values(solution, items_weight, items_values);
    std::chrono::duration<double> elapsed_seconds = end - start;
    double time_taken = elapsed_seconds.count();
    return std::make_tuple(total_profit, time_taken, solution);
}

int main(int argc, char** argv) {
    std::cout << "Branch and bound" << std::endl;
    srand(1);
    bool print_solution = std::stoi(std::string(argv[1]));
    for (int i = 2; i < argc; i += 2) {
        int items_count = std::stoi(argv[i]);
        int sack_size = std::stoi(argv[i + 1]);
        auto [profit, time, solution] = benchmark_dataset(items_count, sack_size);
        std::cout << "Nb items: " << items_count << std::endl;
        std::cout << "Sack size: " << sack_size << std::endl;
        std::cout << "Profit: " << (int)profit << std::endl;
        std::cout << "Time: " << time << std::endl;
        if (print_solution) {
            std::cout << solution.size() << std::endl;
            for (int i : solution) {
                std::cout << i << std::endl;
            }
        }
        std::cout << std::endl;
    }
}