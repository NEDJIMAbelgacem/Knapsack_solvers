#ifndef H_UNBOUNDED_KNAPSACK_SOLVER_DP
#define H_UNBOUNDED_KNAPSACK_SOLVER_DP

#include <vector>
#include <map>

#include "KnapsackSolverAbstract.h"

class UnboundedKnapsackSolverDP : public KnapsackSolverAbstract {
    std::vector<double> weights;
    std::vector<double> values;
    std::map<std::pair<int, double>, std::vector<int>> sub_problem_solution_v;
    std::map<std::pair<int, double>, double> sub_problem_solution;
    std::vector<int> solve_impl(double sack_size, int start_index);
public:
    UnboundedKnapsackSolverDP(std::vector<double> weights, std::vector<double> values);
    
    virtual std::vector<int> solve(double sack_size) override;
    virtual double get_solution(double sack_size) override;
    virtual double get_solution_total_weight(double sack_size) override;
    virtual std::vector<int> get_solution_items(double sack_size) override;
    virtual std::vector<double> get_solution_values(double sack_size) override;
    virtual std::vector<double> get_solution_weights(double sack_size) override;
};

#endif