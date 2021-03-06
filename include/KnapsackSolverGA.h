#ifndef H_KNAPSACK_SOLVER_GA
#define H_KNAPSACK_SOLVER_GA

#include <vector>
#include <map>
#include <algorithm>

#include "KnapsackSolverAbstract.h"

class KnapsackSolverGA {
    std::vector<double> weights;
    std::vector<double> values;
    double sack_size;

    std::vector<int> generateRandomIndividual(double sack_size);
    double calculate_fittness(std::vector<int>& ind, double sack_size);
    std::vector<double> calculate_fittness(std::vector<std::vector<int>> population, double sack_size);
    std::vector<int> selection(std::vector<double> fittness, int nb_selected, const std::vector<std::vector<int>>& population);
    std::vector<std::vector<int>> crossover(const std::vector<std::vector<int>>& parents, int nb_offspring);
    void mutation(std::vector<std::vector<int>>& population);

    std::vector<int> solve_impl(double sack_size);
public:
    KnapsackSolverGA(std::vector<double> weights, std::vector<double> values);
    std::vector<double> fittness_history;

    float mutation_rate = 0.1f;
    float crossover_rate = 0.4f;
    int population_size = 600;
    int generations_count = 100;
    std::vector<int> solve(double sack_size);
};

#endif