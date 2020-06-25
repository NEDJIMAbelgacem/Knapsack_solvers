#ifndef H_KNAPSACK_SOLVER_SA
#define H_KNAPSACK_SOLVER_SA

#include <vector>
#include <map>

class KnapsackSolverSA {
    std::vector<double> weights;
    std::vector<double> values;
    float sack_size;

    std::vector<int> generate_initial_state();
    std::vector<int> pick_random_neighbour(std::vector<int> current_state);
public:
    KnapsackSolverSA(std::vector<double>& weights, std::vector<double>& values, int max_iterations_count=10000);
    std::vector<int> solve(double sack_size);

    float start_temperature;
    float temperature = 20;
    float end_temp = 5.0f;
    float cooling_factor = 0.9;
    int max_iterations_count;
};

#endif