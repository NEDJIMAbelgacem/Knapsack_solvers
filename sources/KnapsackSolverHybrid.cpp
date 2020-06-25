#include "KnapsackSolverHybrid.h"

#include <iostream>
#include <cmath>

#include "Utils.h"

KnapsackSolverHybrid::KnapsackSolverHybrid(std::vector<double> _weights, std::vector<double> _values)
    : weights(_weights), values(_values) { }

std::vector<int> KnapsackSolverHybrid::generateRandomIndividual(double sack_size) {
    std::vector<int> ind;
    for (int i = 0; i < weights.size(); ++i) {
        int max_item_count = sack_size / weights[i];
        if (max_item_count == 0) ind.push_back(0);
        else ind.push_back(rand() % max_item_count + 1);
        sack_size -= weights[i] * ind.back();
    }
    return ind;
}

double KnapsackSolverHybrid::calculate_fittness(std::vector<int>& ind, double sack_size) {
    double weights_sum = 0;
    double values_sum = 0;
    for (int i = 0; i < ind.size(); ++i) {
        weights_sum += weights[i] * ind[i];
        values_sum += values[i] * ind[i];
        if (weights_sum > sack_size) return 0;
    }
    return values_sum;
}

std::vector<double> KnapsackSolverHybrid::calculate_fittness(std::vector<std::vector<int>> population, double sack_size) {
    std::vector<double> fittness;
    fittness.reserve(population.size());
    for (std::vector<int>& ind : population) {
        double f = calculate_fittness(ind, sack_size);
        fittness.push_back(f);
    }
    return fittness;
}

std::vector<int> KnapsackSolverHybrid::selection(std::vector<double> fittness, int nb_selected, const std::vector<std::vector<int>>& population) {
    std::vector<int> selected_individuals;
    for (int i = 0; i < fittness.size(); ++i) selected_individuals.push_back(i);
    // sort according to fittness (decreasing)
    int k = 0;
    std::sort(selected_individuals.begin(), selected_individuals.end(), [&](int a, int b) {
        return fittness[a] > fittness[b];
    });
    selected_individuals.resize(nb_selected);
    return selected_individuals;
}

std::vector<std::vector<int>> KnapsackSolverHybrid::crossover(const std::vector<std::vector<int>>& parents, int nb_offspring) {
    std::vector<std::vector<int>> offspring;
    offspring.reserve(nb_offspring);
    int i = 0;
    while (offspring.size() < nb_offspring) {
        int crossover_point = rand() % ( parents[0].size() / 3 ) + parents[0].size() / 3;
        int parent1 = i % parents.size();
        int parent2 = (i + 1) % parents.size();
        float x = (float)rand() / RAND_MAX;
        if (x > crossover_rate) continue;
        offspring.push_back(std::vector<int>(parents[parent1].size()));
        for (int j = 0; j < parents[parent1].size(); ++j) {
            offspring.back()[j] = j < crossover_point ? parents[parent1][j] : parents[parent2][j];
        }
        if (!is_valid_solution(offspring.back(), weights, values, sack_size)) offspring.pop_back();
        offspring.push_back(std::vector<int>(parents[parent1].size()));
        for (int j = 0; j < parents[parent1].size(); ++j) {
            offspring.back()[j] = j < crossover_point ? parents[parent2][j] : parents[parent1][j];
        }
        if (!is_valid_solution(offspring.back(), weights, values, sack_size)) offspring.pop_back();
        ++i;
    }
    return offspring;
}

void KnapsackSolverHybrid::mutation(std::vector<std::vector<int>>& population) {
    for (int i = 0; i < population.size(); ++i) {
        if ((double)rand()/RAND_MAX > mutation_rate) continue;
        int a = rand() % population[i].size();
        int b = rand() % population[i].size();
        if (a > b) {
            int t = a;
            a = b;
            b = t;
        }
        double w = sack_size - calculate_total_weight(population[i], weights, values);
        for (int j = 0; j < b && j < population[i].size(); ++j) {
            if (weights[j] < w) {
                int k = rand() % (int)(w / weights[j]) + 1;
                population[i][j] += k;
                w -= weights[j] * k;
            } else if (population[i][j] > 0) {
                int k = rand() % population[i][j] + 1;
                population[i][j] -= k;
                w += weights[j] * k;
            }
        }
    }
}

std::vector<int> KnapsackSolverHybrid::solve_impl(double sack_size, int initial_population_size, int generations_count) {
    this->sack_size = sack_size;
    std::vector<std::vector<int>> population;
    std::vector<double> fittness;
    for (int i = 0; i < initial_population_size; ++i) population.push_back(generateRandomIndividual(sack_size));
    std::vector<int> best_solution;
    double best_solution_fittness = 0.0f;

    int num_parents = population.size() / 2;
    int num_offspring = population.size() - num_parents;
    for (int i = 0; i < generations_count; ++i) {
        fittness = calculate_fittness(population, sack_size);
        std::vector<std::vector<int>> parents;
        std::vector<int> selected_parents = selection(fittness, num_parents, population);
        if (fittness[selected_parents[0]] >= best_solution_fittness) {
            best_solution_fittness = fittness[selected_parents[0]];
            best_solution = population[selected_parents[0]];
        }
        for (int j : selected_parents) parents.push_back(population[j]);
        std::vector<std::vector<int>> offsprings = crossover(parents, num_offspring);
        mutation(offsprings);
        population = parents;
        for (std::vector<int> indiv : offsprings) {
            population.push_back(enhance_individual(indiv, max_SA_iterations_count));
        }
    }
    return best_solution;
}

std::vector<int> KnapsackSolverHybrid::enhance_individual(std::vector<int>& state, int max_iterations_count) {
    this->sack_size = sack_size;
    std::vector<int> current_state = state;
    double current_profit = calculate_total_values(current_state, weights, values);
    std::vector<int> best_solution = current_state;
    for (int i = 0; i < max_iterations_count; ++i) {
        std::vector<int> neighbour_state = pick_random_neighbour(current_state);
        double neighbour_profit = calculate_total_values(neighbour_state, weights, values);
        if (neighbour_profit > current_profit) {
            current_state = neighbour_state;
            current_profit = neighbour_profit;
        }
    }
    return best_solution;
}

std::vector<int> KnapsackSolverHybrid::solve(double sack_size) {
    std::vector<int> solution = solve_impl(sack_size, population_size, generations_count);
    return solution;
}

std::vector<int> KnapsackSolverHybrid::pick_random_neighbour(std::vector<int> state) {
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