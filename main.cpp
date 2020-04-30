#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "KnapsackSolverDP.h"
#include "KnapsackSolverBnB.h"
#include "UnboundedKnapsackSolverBnB.h"
#include "UnboundedKnapsackSolverDP.h"

void test_dp(std::vector<double> items_weight, std::vector<double> values, double sack_weight) {
    KnapsackSolverDP solver(items_weight, values);
    double solution_value = solver.get_solution(sack_weight);
    std::cout << "Weights : ";
    for (double w : items_weight) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "Values : ";
    for (double w : values) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "Solution : " << solution_value << std::endl;
    std::cout << "Items : ";
    for (double v : solver.get_solution_items(sack_weight)) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Solution's total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

void test_bnb(std::vector<double> items_weight, std::vector<double> values, double sack_weight) {
    KnapsackSolverBnB solver(items_weight, values);
    double solution_value = solver.get_solution(sack_weight);
    std::cout << "Weights : ";
    for (double w : items_weight) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "Values : ";
    for (double w : values) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "Solution : " << solution_value << std::endl;
    std::cout << "Items : ";
    for (double v : solver.get_solution_items(sack_weight)) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Solution's total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

void test_unbounded_bnb(std::vector<double> items_weight, std::vector<double> values, double sack_weight) {
    UnboundedKnapsackSolverBnB solver(items_weight, values);
    double solution_value = solver.get_solution(sack_weight);
    std::cout << "Weights : ";
    for (double w : items_weight) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "Values : ";
    for (double w : values) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "Solution : " << solution_value << std::endl;
    std::cout << "Items : ";
    for (double v : solver.get_solution_items(sack_weight)) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Solution's total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

void test_unbounded_dp(std::vector<double> items_weight, std::vector<double> values, double sack_weight) {
    UnboundedKnapsackSolverDP solver(items_weight, values);
    double solution_value = solver.get_solution(sack_weight);
    std::cout << "Weights : "; 
    for (double w : items_weight) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "Values : ";
    for (double w : values) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "Solution : " << solution_value << std::endl;
    std::cout << "Items : ";
    for (double v : solver.get_solution_items(sack_weight)) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Solution's total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

void generate_random_instance(int nb_items, std::vector<double>& items_weight, std::vector<double>& values, double min_item_weight=10, double min_item_value=10, double max_item_weight=100, double max_item_value=100) {
    items_weight.clear();
    values.clear();
    for (int i = 0; i < nb_items; ++i) {
        items_weight.push_back(min_item_weight + rand() % (int)(max_item_weight - min_item_weight));
        values.push_back(min_item_value + rand() % (int)(max_item_value - min_item_value));
    }
}

void read_data(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size) {
    std::ifstream in(file_name, std::ios::in);
    weights.clear();
    values.clear();
    if (!in.is_open()) return;
    std::string line;
    // comment lines
    std::getline(in, line);
    std::getline(in, line);
    std::getline(in, line);
    // items count
    std::string place_holder;
    int items_count;
    in >> place_holder >> items_count; in.ignore();
    std::getline(in, line);
    // sack_size
    in >> place_holder >> sack_size; in.ignore();
    std::getline(in, line);
    std::getline(in, line);
    // begin data
    std::getline(in, line);
    assert(line == "begin data ");
    // 
    for (int i = 0; i < items_count; ++i) {
        double w, v;
        in >> w >> v; in.ignore();
        weights.push_back(w);
        values.push_back(v);
    }
    in.close();
}

int main(int argc, char** argv) {
    std::vector<double> items_weight, values;
    double sack_weight = 300;
    std::cout << "Entrez la taille d'instance : ";
    int taille_instance;
    std::cin >> taille_instance;
    if (argc < 2) generate_random_instance(taille_instance, items_weight, values, 10, 80);
    else read_data(std::string(argv[1]), items_weight, values, sack_weight);

    // std::cout << "=================================================" << std::endl;
    // std::cout << "0/1 Bnanch & Bound test :" << std::endl;
    // std::cout << "=================================================" << std::endl;
    // test_bnb(items_weight, values, sack_weight);
    // std::cout << "=================================================" << std::endl;
    // std::cout << "0/1 dynamic programming test :" << std::endl;
    // std::cout << "=================================================" << std::endl;
    // test_dp(items_weight, values, sack_weight);
    std::cout << "=================================================" << std::endl;
    std::cout << "Unbounded Bnanch & Bound test :" << std::endl;
    std::cout << "=================================================" << std::endl;
    test_unbounded_bnb(items_weight, values, sack_weight);
    std::cout << "=================================================" << std::endl;
    std::cout << "Unbounded dynamic programming test :" << std::endl;
    std::cout << "=================================================" << std::endl;
    test_unbounded_dp(items_weight, values, sack_weight);
    std::cin.get();
    std::cin >> taille_instance;
}
