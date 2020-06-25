#ifndef H_KNAPSACK_SOLVER_HYBRID
#define H_KNAPSACK_SOLVER_HYBRID

#include <vector>
#include <map>
#include <algorithm>

#include "KnapsackSolverAbstract.h"

class KnapsackSolverHybrid {
    std::vector<double> weights;
    std::vector<double> values;
    double sack_size;

    float ALPHA = 0.99;
    float temperature = .99;
    int max_iterations_count;

    std::vector<int> generateRandomIndividual(double sack_size);
    double calculate_fittness(std::vector<int>& ind, double sack_size);
    std::vector<double> calculate_fittness(std::vector<std::vector<int>> population, double sack_size);
    std::vector<int> selection(std::vector<double> fittness, int nb_selected, const std::vector<std::vector<int>>& population);
    std::vector<std::vector<int>> crossover(const std::vector<std::vector<int>>& parents, int nb_offspring);
    void mutation(std::vector<std::vector<int>>& population);

    std::vector<int> pick_random_neighbour(std::vector<int> current_state);
    // simulated annealing round
    std::vector<int> enhance_individual(std::vector<int>& ind, int max_iterations);

    std::vector<int> solve_impl(double sack_size, int initial_population_size, int generations_count);
public:
    KnapsackSolverHybrid(std::vector<double> weights, std::vector<double> values);

    float mutation_rate = 0.4f;
    float crossover_rate = 0.4f;
    int population_size = 120;
    int generations_count = 300;
    int max_SA_iterations_count = 100;
    std::vector<int> solve(double sack_size);
};

#endif