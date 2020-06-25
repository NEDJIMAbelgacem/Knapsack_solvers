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

#include "UnboundedKnapsackSolverHeur.h"
#include "Utils.h"


// <taille_instance> <sack_weight> <random | ukp_dataset>
int main(int argc, char** argv) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    srand(0);
    std::vector<double> items_weight, items_values;
    int taille_instance = std::stoi(std::string(argv[1]));
    double sack_weight = std::stod(std::string(argv[2]));

    if (std::string(argv[argc - 1]) == "random") generate_random_instance(taille_instance, items_weight, items_values, 10, 80);
    else read_ukp_datset(std::string(argv[argc - 1]), items_weight, items_values, sack_weight);
    sack_weight = std::stoi(std::string(argv[2]));
    
    std::vector<int> solution;
    if (std::string(argv[3]) == "value-ordered") {
        auto heur_function = [&](int a, int b) {
            return items_values[a] > items_values[b];
        };
        UnboundedKnapsackSolverHeur solver(items_weight, items_values, heur_function);
        start = std::chrono::system_clock::now();
        solution = solver.solve(sack_weight);
        end = std::chrono::system_clock::now();
    } else if (std::string(argv[3]) == "density-ordered") {
        auto heur_function = [&](int a, int b) {
            return items_values[a] / items_weight[a] > items_values[b] / items_weight[b];
        };
        UnboundedKnapsackSolverHeur solver(items_weight, items_values, heur_function);
        start = std::chrono::system_clock::now();
        solution = solver.solve(sack_weight);
        end = std::chrono::system_clock::now();
    }
    std::vector<int> items_repertition(items_weight.size(), 0);
    for (int i : solution) items_repertition[i]++;
    std::cout << items_repertition.size() << std::endl;
    for (int i : items_repertition) std::cout << i << std::endl;

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << std::endl;
}
