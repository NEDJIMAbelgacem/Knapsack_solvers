#include "KnapsackSolverBnB.h"

KnapsackSolverBnB::KnapsackSolverBnB(std::vector<double> _weights, std::vector<double> _values)
    : weights(_weights), values(_values) {
        items_sorted.reserve(weights.size());
        items_values_sum = 0;
        for (int i = 0; i < weights.size(); ++i) {
            items_sorted[i] = i;;
            items_values_sum += values[i];
        }
        std::sort(items_sorted.begin(), items_sorted.end(), [&](int a, int b) {
            return items_sorted[a] > items_sorted[b];
        });
    }

std::pair<double, std::vector<int>> KnapsackSolverBnB::solve_impl(double sack_size, int curr_item, double cumulated, double best_possible_solution, double& best_solution_so_far) {
    if (curr_item >= weights.size()) return std::make_pair(cumulated, std::vector<int>{ });
    // branch out condition
    if (best_possible_solution < best_solution_so_far) return std::make_pair(cumulated, std::vector<int>{ });
    int i = items_sorted[curr_item];

    // OUT
    std::pair<double, std::vector<int>> sub_problem1 = solve_impl(sack_size, curr_item + 1, cumulated, best_possible_solution - values[i], best_solution_so_far);
    best_solution_so_far = std::max(best_solution_so_far, sub_problem1.first);

    // IN
    std::pair<double, std::vector<int>> sub_problem2 = { 0.0, std::vector<int>{ } };
    if (sack_size >= weights[i]) {
        sub_problem2 = solve_impl(sack_size - weights[i], curr_item + 1, cumulated + values[i], best_possible_solution, best_solution_so_far);
        sub_problem2.second.push_back(i);
        best_solution_so_far = std::max(best_solution_so_far, sub_problem2.first);
    }

    // 
    if (sub_problem1.first > sub_problem2.first) return sub_problem1;
    return sub_problem2;
}

void KnapsackSolverBnB::solve(double sack_size) {
    if (sub_problem_solution.find(sack_size) != sub_problem_solution.end()) return;
    double best = 0.0;
    auto [solution, solution_items] = solve_impl(sack_size, 0, 0.0, items_values_sum, best);
    sub_problem_solution[sack_size] = solution;
    sub_problem_solution_v[sack_size] = solution_items;
}

double KnapsackSolverBnB::get_solution(double sack_size) {
    solve(sack_size);
    return sub_problem_solution[sack_size];
}

double KnapsackSolverBnB::get_solution_total_weight(double sack_size) {
    double w = 0.0;
    for (int i : get_solution_items(sack_size)) w += weights[i];
    return w;
}

std::vector<int> KnapsackSolverBnB::get_solution_items(double sack_size) {

    solve(sack_size);
    return sub_problem_solution_v[sack_size];
}

std::vector<double> KnapsackSolverBnB::get_solution_values(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(values[i]);
    return res;
}

std::vector<double> KnapsackSolverBnB::get_solution_weights(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(weights[i]);
    return res;
}