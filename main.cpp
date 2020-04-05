#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>

#include "KnapsackSolverDP.h"
#include "KnapsackSolverBnB.h"

void test_dp() {
    std::vector<double> items_weight;
    std::vector<double> values;
    for (int i = 0; i < 10; ++i) {
        items_weight.push_back(rand() % 100);
        values.push_back(rand() % 100);
    }
    double sack_weight = 100.0;
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
    std::cout << "Solution total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

void test_bnb() {
    std::vector<double> items_weight;
    std::vector<double> values;
    for (int i = 0; i < 10; ++i) {
        items_weight.push_back(rand() % 100);
        values.push_back(rand() % 100);
    }
    double sack_weight = 200.0;
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
    std::cout << "Solution total weight : " << solver.get_solution_total_weight(sack_weight) << std::endl;
}

int main(int, char**) {
    std::cout << "=================================================" << std::endl;
    std::cout << "Dynamic programming test :" << std::endl;
    std::cout << "=================================================" << std::endl;
    test_dp();
    std::cout << "=================================================" << std::endl;
    std::cout << "Bnanch & Bound test :" << std::endl;
    std::cout << "=================================================" << std::endl;
    test_bnb();
    std::cin.get();
}
