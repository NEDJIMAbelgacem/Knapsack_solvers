#include "UnboundedKnapsackSolverDP.h"

UnboundedKnapsackSolverDP::UnboundedKnapsackSolverDP(std::vector<double> _weights, std::vector<double> _values)
    : weights(_weights), values(_values) { }

std::vector<int> UnboundedKnapsackSolverDP::solve_impl(double sack_size, int start_index) {
    std::pair<int, double> problem_instance = { start_index, sack_size };
    if (start_index >= weights.size()) {
        sub_problem_solution[problem_instance] = 0.0;
        sub_problem_solution_v[problem_instance] = std::vector<int>{ };
    }
    if (sub_problem_solution.find(problem_instance) != sub_problem_solution.end()) return sub_problem_solution_v[problem_instance];

    // OUT 
    solve_impl(sack_size, start_index + 1);
    std::pair<int, double> sub_problem1 = { start_index + 1, sack_size };
    double sub_problem1_solution = sub_problem_solution[sub_problem1];
    
    // IN
    std::pair<int, double> sub_problem2 = { start_index, sack_size - weights[start_index]};
    double sub_problem2_solution = sub_problem1_solution;
    if (sack_size >= weights[start_index]) {
        solve_impl(sack_size - weights[start_index], start_index);
        sub_problem2_solution = values[start_index] + sub_problem_solution[sub_problem2];
    }

    // current problem solution
    if (sub_problem1_solution >= sub_problem2_solution) {
        sub_problem_solution[problem_instance] = sub_problem1_solution;
        sub_problem_solution_v[problem_instance] = sub_problem_solution_v[sub_problem1];
    } else {
        sub_problem_solution[problem_instance] = sub_problem2_solution;
        sub_problem_solution_v[problem_instance] = sub_problem_solution_v[sub_problem2];
        sub_problem_solution_v[problem_instance].push_back(start_index);
    }
    return sub_problem_solution_v[problem_instance];
}

std::vector<int> UnboundedKnapsackSolverDP::solve(double sack_size) {
    return solve_impl(sack_size, 0);
}

double UnboundedKnapsackSolverDP::get_solution(double sack_size) {
    std::pair<int, double> problem_instance = { 0, sack_size };
    if (sub_problem_solution.find(problem_instance) == sub_problem_solution.end()) solve(sack_size);
    return sub_problem_solution[std::make_pair(0, sack_size)];
}

double UnboundedKnapsackSolverDP::get_solution_total_weight(double sack_size) {
    double w = 0.0;
    for (int i : get_solution_items(sack_size)) w += weights[i];
    return w;
}

std::vector<int> UnboundedKnapsackSolverDP::get_solution_items(double sack_size) {
    solve(sack_size);
    return sub_problem_solution_v[std::make_pair(0, sack_size)];
}

std::vector<double> UnboundedKnapsackSolverDP::get_solution_values(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(values[i]);
    return res;
}

std::vector<double> UnboundedKnapsackSolverDP::get_solution_weights(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(weights[i]);
    return res;
}