#include "KnapsackSolverSA.h"
#include "Utils.h"

#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>

KnapsackSolverSA::KnapsackSolverSA(std::vector<double>& _weights, std::vector<double>& _values, int _max_iterations_count)
: weights(_weights), values(_values), max_iterations_count(_max_iterations_count) {

}

std::vector<int> KnapsackSolverSA::solve(double sack_size) {
    this->sack_size = sack_size;
    double temperature = start_temperature;


    std::vector<int> current_state = generate_initial_state();

    double current_cost;
    std::vector<int> best_solution = current_state;
    double best_profit = calculate_total_values(current_state, weights, values);
    while (temperature > end_temp) {
        for (int i = 0; i < max_iterations_count; ++i) {
            current_cost = calculate_total_values(current_state, weights, values);
            std::vector<int> neighbour_state = pick_random_neighbour(current_state);
            double neighbour_profit = calculate_total_values(neighbour_state, weights, values);
            double delta = neighbour_profit - current_cost;
            if (delta > 0) {
                current_state = neighbour_state;
                if (neighbour_profit > best_profit) {
                    best_solution = current_state;
                    best_profit = neighbour_profit;
                }
            } else {
                float v = exp(delta / temperature);
                if (v > (float)rand()/RAND_MAX)
                    current_state = neighbour_state;
            }
        }
        temperature *= cooling_factor;
    }
    return best_solution;
}

std::vector<int> KnapsackSolverSA::generate_initial_state() 
{
    std::vector<int> state;
    state.reserve(weights.size());
    int available_w = sack_size;
    for (int i = 0; i < weights.size(); ++i) {
        int m = available_w / weights[i] / 2;
        int k = rand() % (m + 1);
        state.push_back(k);
        available_w -= k * weights[i];
    }
    return state;
}

std::vector<int> KnapsackSolverSA::pick_random_neighbour(std::vector<int> state) {
    int x = rand() % state.size();
    double capacity_left = sack_size - calculate_total_weight(state, weights, values);
    std::vector<int> possible_items;
    for (int i = 0; i < state.size(); ++i) {
        if (capacity_left > weights[i]) {
            possible_items.push_back(i);
        }
    } 
    if (possible_items.size() != 0) {
        int ind = rand() % possible_items.size();
        state[possible_items[ind]] += rand() % (int)(capacity_left / weights[possible_items[ind]]) + 1;
    } else {
        std::vector<int> picked_items;
        for (int i = 0; i < state.size(); ++i) {
            if (state[i] > 0) {
                picked_items.push_back(i);
            }
        }
        if (picked_items.size() != 0) {
            int ind = rand() % picked_items.size();
            int n_items = rand() % state[picked_items[ind]] + 1;
            state[picked_items[ind]] -= n_items;
            capacity_left += n_items * weights[picked_items[ind]];
            std::vector<int> valid_add;
            do {
                for (int i = 0; i < state.size(); ++i) {
                    if (i == ind) continue;
                    if (capacity_left >= weights[i]) {
                        valid_add.push_back(i);
                    }
                }
                if (valid_add.size() > 0) {
                    int r = rand() % valid_add.size();
                    int n = capacity_left / weights[valid_add[r]];
                    state[valid_add[r]] += n;
                    capacity_left -= n * weights[valid_add[r]];
                }
            } while (valid_add.size() != 0);
        }
    }
    return state;
}