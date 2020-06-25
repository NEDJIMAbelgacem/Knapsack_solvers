#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "KnapsackSolverHybrid.h"
#include "Utils.h"

int main(int argc, char** argv) {
    srand(0);
    std::vector<double> items_weight, items_values;
    int taille_instance = std::stoi(argv[1]);
    double sack_weight = std::stod(argv[2]);

    int GA_population_size = std::stoi(argv[3]);
    int GA_generations_count = std::stoi(argv[4]);
    int max_SA_iterations_count = std::stoi(argv[5]);

    if (std::string(argv[argc - 1]) == "random") generate_random_instance(taille_instance, items_weight, items_values, 10, 80);
    else read_ukp_datset(std::string(argv[argc - 1]), items_weight, items_values, sack_weight);    

    std::cout << items_weight.size() << " " << sack_weight << std::endl;
    for (int i = 0; i < 10; ++i) std::cout << items_weight[i] << " ";
    std::cout << std::endl;
    KnapsackSolverHybrid solver(items_weight, items_values);
    if (argc >= 5) {
        solver.population_size = GA_population_size;
        solver.generations_count = GA_generations_count;
        solver.max_SA_iterations_count = max_SA_iterations_count;
    }
    std::vector<int> solution = solver.solve(sack_weight);
    std::cout << "Solution's total profit : " << calculate_total_values(solution, items_weight, items_values) << std::endl;
}
