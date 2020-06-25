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

#include "KnapsackSolverSA.h"
#include "Utils.h"

std::tuple<double, double, std::vector<int>> benchmark_dataset(std::string dataset_file, int max_iterations_count, double sack_size) {
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
    std::map<std::string, double> params = get_SA_parameters(dataset_name);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<double> items_weight, items_values;
    double _;
    read_ukp_datset(dataset_file, items_weight, items_values, _);

    KnapsackSolverSA solver(items_weight, items_values);
    solver.start_temperature = params["temperature initiale"];
    solver.max_iterations_count = max_iterations_count; //params["sampling size"];
    solver.end_temp = params["temperature finale"];
    solver.cooling_factor = params["taux de refroidissement"];

    start = std::chrono::system_clock::now();
    std::vector<int> solution = solver.solve(sack_size);
    end = std::chrono::system_clock::now();
    double total_profit = calculate_total_values(solution, items_weight, items_values );
    std::chrono::duration<double> elapsed_seconds = end - start;
    double time_taken = elapsed_seconds.count();
    return std::make_tuple(total_profit, time_taken, solution);
}


int main(int argc, char** argv) {
    srand(1);
    std::vector<double> items_weight, items_values;
    int taille_instance = std::stoi(std::string(argv[1]));
    double sack_weight = std::stod(std::string(argv[2]));
    int nb_iterations = std::stoi(std::string(argv[3]));

    auto [profit, time, solution] = benchmark_dataset(argv[argc - 1], nb_iterations, sack_weight);

    // if (std::string(argv[argc - 1]) == "random") generate_random_instance(taille_instance, items_weight, items_values, 10, 80);
    // else  read_ukp_datset(std::string(argv[argc - 1]), items_weight, items_values, sack_weight);
    // sack_weight = std::stod(std::string(argv[2]));

    std::cout << solution.size() << std::endl;
    for (int i : solution) {
        std::cout << i << std::endl;
    }
    std::cout << time << std::endl;
}
