#include "KnapsackSolverGA.h"
#include <iostream>

#include "Utils.h"

KnapsackSolverGA::KnapsackSolverGA(std::vector<double> _weights, std::vector<double> _values)
    : weights(_weights), values(_values) { }

std::vector<int> KnapsackSolverGA::generateRandomIndividual(double sack_size) {
    std::vector<int> ind;
    for (int i = 0; i < weights.size(); ++i) {
        int max_item_count = sack_size / weights[i];
        if (max_item_count == 0) ind.push_back(0);
        else ind.push_back(rand() % max_item_count + 1);
        sack_size -= weights[i] * ind.back();
    }
    return ind;
}

double KnapsackSolverGA::calculate_fittness(std::vector<int>& ind, double sack_size) {
    double weights_sum = 0;
    double values_sum = 0;
    for (int i = 0; i < ind.size(); ++i) {
        weights_sum += weights[i] * ind[i];
        values_sum += values[i] * ind[i];
        if (weights_sum > sack_size) return 0;
    }
    return values_sum;
}

std::vector<double> KnapsackSolverGA::calculate_fittness(std::vector<std::vector<int>> population, double sack_size) {
    std::vector<double> fittness;
    fittness.reserve(population.size());
    for (std::vector<int>& ind : population) {
        double f = calculate_fittness(ind, sack_size);
        fittness.push_back(f);
    }
    return fittness;
}

std::vector<int> KnapsackSolverGA::selection(std::vector<double> fittness, int nb_selected, const std::vector<std::vector<int>>& population) {
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

std::vector<std::vector<int>> KnapsackSolverGA::crossover(const std::vector<std::vector<int>>& parents, int nb_offspring) {
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

void KnapsackSolverGA::mutation(std::vector<std::vector<int>>& population) {
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

std::vector<int> KnapsackSolverGA::solve_impl(double sack_size) {
    this->sack_size = sack_size;
    std::vector<std::vector<int>> population;
    std::vector<double> fittness;
    for (int i = 0; i < population_size; ++i) population.push_back(generateRandomIndividual(sack_size));
    std::vector<int> best_solution;
    double best_solution_fittness = 0.0f;

    int num_parents = population.size() / 2;
    int num_offspring = population.size() - num_parents;
    for (int i = 0; i < generations_count; ++i) {
        fittness = calculate_fittness(population, sack_size);
        fittness_history.push_back(*std::max_element(fittness.begin(), fittness.end()));
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
        for (std::vector<int>& ind : offsprings) population.push_back(ind);
    }
    return best_solution;
}

std::vector<int> KnapsackSolverGA::solve(double sack_size) {
    std::vector<int> solution = solve_impl(sack_size);
    return solution;
}