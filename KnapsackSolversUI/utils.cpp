#include "utils.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <algorithm>

double calculate_total_weight(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values) {
    int w = 0.0f;
    for (int i = 0; i < solution.size(); ++i) w += solution[i] * weights[i];
    return w;
}

double calculate_total_values(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values) {
    int v = 0.0f;
    for (int i = 0; i < solution.size(); ++i) v += solution[i] * values[i];
    return v;
}
