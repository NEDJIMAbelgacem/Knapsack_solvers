#ifndef H_UNBOUNDED_KNAPSACK_SOLVER_HEUR
#define H_UNBOUNDED_KNAPSACK_SOLVER_HEUR

#include <vector>
#include <map>
#include <algorithm>

#include "KnapsackSolverAbstract.h"

template<typename HeuristicFunc>
class UnboundedKnapsackSolverHeur : public KnapsackSolverAbstract {
private:
    HeuristicFunc heuristic;
    std::vector<double> weights;
    std::vector<double> values;
    std::map<double, std::vector<int>> sub_problem_solution_v;
    std::map<double, double> sub_problem_solution;
public:
    UnboundedKnapsackSolverHeur(std::vector<double> weights, std::vector<double> values, HeuristicFunc heristic_function) {
        this->weights = weights;
        this->values = values;
        heuristic = heristic_function;
    }
    
    virtual void solve(double sack_size) override {
        std::vector<int> valid_choices;
        for (int i = 0; i < values.size(); ++i) {
            if (weights[i] <= sack_size) valid_choices.push_back(i);
        }
        std::sort(valid_choices.begin(), valid_choices.end(), heuristic);
        std::vector<int> selected_items;
        double values_sum = 0.0;
        for (int i : valid_choices) {
            if (weights[i] > sack_size) continue;
            selected_items.push_back(i);
            values_sum += values[i];
            sack_size -= weights[i];
        }
        sub_problem_solution_v[sack_size] = selected_items;
        sub_problem_solution[sack_size] = values_sum;
    }
    virtual double get_solution(double sack_size) override {
        if (sub_problem_solution_v.find(sack_size) == sub_problem_solution_v.end()) solve(sack_size);
        return sub_problem_solution[sack_size];
    }
    virtual double get_solution_total_weight(double sack_size) override {
        if (sub_problem_solution_v.find(sack_size) == sub_problem_solution_v.end()) solve(sack_size);
        double total_weight = 0.0;
        for (int i : sub_problem_solution_v[sack_size]) total_weight += weights[i];
        return total_weight;
    }
    virtual std::vector<int> get_solution_items(double sack_size) override {
        if (sub_problem_solution_v.find(sack_size) == sub_problem_solution_v.end()) solve(sack_size);
        return sub_problem_solution_v[sack_size];
    }
    virtual std::vector<double> get_solution_values(double sack_size) override {
        if (sub_problem_solution_v.find(sack_size) == sub_problem_solution_v.end()) solve(sack_size);
        std::vector<double> res;
        for (int i : sub_problem_solution_v[sack_size]) res.push_back(values[i]);
        return res;
    }
    virtual std::vector<double> get_solution_weights(double sack_size) override {
        if (sub_problem_solution_v.find(sack_size) == sub_problem_solution_v.end()) solve(sack_size);
        std::vector<double> res;
        for (int i : sub_problem_solution_v[sack_size]) res.push_back(values[i]);
        return res;
    }
};

#endif