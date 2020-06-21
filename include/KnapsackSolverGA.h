#ifndef H_KNAPSACK_SOLVER_GA
#define H_KNAPSACK_SOLVER_GA

#include <vector>
#include <map>
#include <algorithm>

#include "KnapsackSolverAbstract.h"

// struct Individual {
//     std::vector<int> genes;
// };


class KnapsackSolverGA : public KnapsackSolverAbstract {
    std::vector<double> weights;
    std::vector<double> values;
    std::map<std::pair<int, double>, std::vector<int>> sub_problem_solution_v;
    std::map<std::pair<int, double>, double> sub_problem_solution;
    double sack_size;

    bool is_valid_individual(std::vector<int>& ind) {
        double w = 0.0;
        for (int i = 0; i < ind.size(); ++i) w += weights[i] * ind[i];
        return w <= sack_size;
    }

    std::vector<int> generateRandomIndividual(double sack_size);
    double calculate_fittness(std::vector<int>& ind, double sack_size);
    std::vector<double> calculate_fittness(std::vector<std::vector<int>> population, double sack_size);
    std::vector<int> selection(std::vector<double> fittness, int nb_selected, const std::vector<std::vector<int>>& population);
    std::vector<std::vector<int>> crossover(const std::vector<std::vector<int>>& parents, int nb_offspring);
    void mutation(std::vector<std::vector<int>>& population);

    void solve_impl(double sack_size, int initial_population_size, int generations_count);
public:
    KnapsackSolverGA(std::vector<double> weights, std::vector<double> values);
    
    virtual void solve(double sack_size) override;
    virtual double get_solution(double sack_size) override;
    virtual double get_solution_total_weight(double sack_size) override;
    virtual std::vector<int> get_solution_items(double sack_size) override;
    virtual std::vector<double> get_solution_values(double sack_size) override;
    virtual std::vector<double> get_solution_weights(double sack_size) override;
};

#endif