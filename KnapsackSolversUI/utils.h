#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <algorithm>

double calculate_total_weight(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values);

double calculate_total_values(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values);


#endif // UTILS_H
