#include "KnapsackSolverGA.h"
#include <iostream>

KnapsackSolverGA::KnapsackSolverGA(std::vector<double> _weights, std::vector<double> _values)
    : weights(_weights), values(_values) { }

std::vector<int> KnapsackSolverGA::generateRandomIndividual(double sack_size) {
    std::vector<int> ind;
    for (int i = 0; i < weights.size(); ++i) {
        int max_item_count = sack_size / weights[i];
        if (max_item_count == 0) ind.push_back(0);
        else ind.push_back(rand() % max_item_count);
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
    for (int i : selected_individuals) std::cout << fittness[i] << " ";
    std::cout << std::endl;
    selected_individuals.resize(nb_selected);
    return selected_individuals;
}

std::vector<std::vector<int>> KnapsackSolverGA::crossover(const std::vector<std::vector<int>>& parents, int nb_offspring) {
    std::vector<std::vector<int>> offspring;
    offspring.reserve(nb_offspring);
    int crossover_point = rand() % ( parents[0].size() / 3 ) + parents[0].size() / 3;
    float crossover_rate = 0.8f;
    int i = 0;
    while (offspring.size() < nb_offspring) {
        int parent1 = i % parents.size();
        int parent2 = (i + 1) % parents.size();
        float x = (float)rand() / RAND_MAX;
        if (x > crossover_rate) continue;
        offspring.push_back(std::vector<int>(parents[parent1].size()));
        for (int j = 0; j < parents[parent1].size(); ++j) {
            offspring.back()[j] = j < crossover_point ? parents[parent1][j] : parents[parent2][j];
        }
        ++i;
    }
    return offspring;
}

void KnapsackSolverGA::mutation(std::vector<std::vector<int>>& population) {
    float mutation_rate = 0.4f;
    for (int i = 0; i < population.size(); ++i) {
        int j = rand() % population[i].size();
        while (j < population[i].size()) {
            float r = (float)rand() / RAND_MAX;
            if (r < mutation_rate) {
                int past_item_count = population[i][j];
                population[i][j]++;
                if (!is_valid_individual(population[i])) population[i][j] -= 2;
            }
            int interval = population[i].size() - j;
            if (interval <= 1) j++;
            else j += rand() % interval;
        }
    }
}

void KnapsackSolverGA::solve_impl(double sack_size, int initial_population_size, int generations_count) {
    this->sack_size = sack_size;
    std::vector<std::vector<int>> population;
    std::vector<double> fittness;
    for (int i = 0; i < initial_population_size; ++i) population.push_back(generateRandomIndividual(sack_size));

    int num_parents = population.size() / 2;
    int num_offspring = population.size() - num_parents;
    for (int i = 0; i < generations_count; ++i) {
        fittness = calculate_fittness(population, sack_size);
        std::cout << "Maximum fittness : " << *std::max_element(fittness.begin(), fittness.end()) << std::endl;
        std::vector<std::vector<int>> parents;
        for (int j : selection(fittness, num_parents, population)) parents.push_back(population[j]);
        std::vector<std::vector<int>> offsprings = crossover(parents, num_offspring);
        mutation(offsprings);
        population = offsprings;
    }

}

void KnapsackSolverGA::solve(double sack_size) {
    solve_impl(sack_size, 100, 20);
}

double KnapsackSolverGA::get_solution(double sack_size) {
    solve(sack_size);
    return sub_problem_solution[std::make_pair(0, sack_size)];
}

double KnapsackSolverGA::get_solution_total_weight(double sack_size) {
    double w = 0.0;
    for (int i : get_solution_items(sack_size)) w += weights[i];
    return w;
}

std::vector<int> KnapsackSolverGA::get_solution_items(double sack_size) {
    solve(sack_size);
    return sub_problem_solution_v[std::make_pair(0, sack_size)];
}

std::vector<double> KnapsackSolverGA::get_solution_values(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(values[i]);
    return res;
}

std::vector<double> KnapsackSolverGA::get_solution_weights(double sack_size) {
    std::vector<double> res;
    for (int i : get_solution_items(sack_size)) res.push_back(weights[i]);
    return res;
}