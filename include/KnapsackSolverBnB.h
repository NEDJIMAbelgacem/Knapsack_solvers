#ifndef H_KNAPSACK_SOLVER_BNB
#define H_KNAPSACK_SOLVER_BNB

#include <vector>
#include <map>
#include <algorithm>

#include "KnapsackSolverAbstract.h"

class KnapsackSolverBnB : public KnapsackSolverAbstract {
private:
    std::vector<double> weights;
    std::vector<double> values;
    std::map<double, std::vector<int>> sub_problem_solution_v;
    std::map<double, double> sub_problem_solution;

    std::vector<int> items_sorted;
    double items_values_sum = 0;
    std::pair<double, std::vector<int>> solve_impl(double sack_size, int curr_item, double cumulated, double best_possible_solution, double& best_solution_so_far);
public:
    KnapsackSolverBnB(std::vector<double> weights, std::vector<double> values);
    
    virtual void solve(double sack_size) override;
    virtual double get_solution(double sack_size) override;
    virtual double get_solution_total_weight(double sack_size) override;
    virtual std::vector<int> get_solution_items(double sack_size) override;
    virtual std::vector<double> get_solution_values(double sack_size) override;
    virtual std::vector<double> get_solution_weights(double sack_size) override;
};

#endif