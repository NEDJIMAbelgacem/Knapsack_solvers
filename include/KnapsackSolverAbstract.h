#ifndef H_KNAPSACK_SOLVER_ABSTRACT
#define H_KNAPSACK_SOLVER_ABSTRACT

#include <vector>

class KnapsackSolverAbstract {
public:
    virtual std::vector<int> solve(double sack_size) = 0;
    virtual double get_solution(double sack_size) = 0;
    virtual double get_solution_total_weight(double sack_size) = 0;
    virtual std::vector<int> get_solution_items(double sack_size) = 0;
    virtual std::vector<double> get_solution_values(double sack_size) = 0;
    virtual std::vector<double> get_solution_weights(double sack_size) = 0;
};

#endif