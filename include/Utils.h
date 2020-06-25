#ifndef H_KNAPSACK_UTILS
#define H_KNAPSACK_UTILS

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

std::map<std::string, double> get_SA_parameters(std::string dataset_name);
std::map<std::string, double> get_GA_parameters(std::string dataset_name);

std::vector<int> convertToNsolution(std::vector<int>& items, int nb_items);

double calculate_total_weight(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values);

double calculate_total_values(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values);

bool is_valid_solution(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values, double sack_size);

void generate_random_instance(int nb_items, std::vector<double>& items_weight, std::vector<double>& values, double min_item_weight=10, double min_item_value=10, double max_item_weight=100, double max_item_value=100);

void read_data(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size);
void read_ukp_datset(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size);

#endif