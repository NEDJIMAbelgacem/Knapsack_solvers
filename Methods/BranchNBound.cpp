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

#include "UnboundedKnapsackSolverBnB.h"
#include "Utils.h"

int main(int argc, char** argv) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    srand(0);
    std::vector<double> items_weight, items_values;
    double sack_weight = 2000;
    int taille_instance = 1000;
    taille_instance = std::stoi(std::string(argv[1]));
    
    if (std::string(argv[argc - 1]) == "random") generate_random_instance(taille_instance, items_weight, items_values, 10, 80);
    else read_ukp_datset(std::string(argv[argc - 1]), items_weight, items_values, sack_weight);
    sack_weight = std::stod(std::string(argv[2]));
    
    UnboundedKnapsackSolverBnB solver(items_weight, items_values);

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_weight);
    end = std::chrono::system_clock::now();

    std::vector<int> items_repertition(items_weight.size(), 0);
    for (int i : solution) items_repertition[i]++;
    std::cout << items_repertition.size() << std::endl;
    for (int i : items_repertition) std::cout << i << std::endl;

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << std::endl;
}
