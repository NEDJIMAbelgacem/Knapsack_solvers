
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <algorithm>

#include "Utils.h"

using namespace std;

std::map<std::string, double> get_SA_parameters(std::string dataset_name) {
    std::map<std::string, double> params;
    if (dataset_name == "DifficileGrande") {
        params["sampling size"] = 90;
        params["temperature initiale"] = 1000;
        params["taux de refroidissement"] = 0.7;
        params["temperature finale"] = 50;
    } else if (dataset_name == "DifficuleMoyenne") {
        params["sampling size"] = 40;
        params["temperature initiale"] = 400;
        params["taux de refroidissement"] = 0.82;
        params["temperature finale"] = 250;
    } else if (dataset_name == "DifficulePetite") {
        params["sampling size"] = 50;
        params["temperature initiale"] = 600;
        params["taux de refroidissement"] = 0.82;
        params["temperature finale"] = 250;
    } else if (dataset_name == "FacileGrande") {
        params["sampling size"] = 5;
        params["temperature initiale"] = 600;
        params["taux de refroidissement"] = 0.7;
        params["temperature finale"] = 50;
    } else if (dataset_name == "FacileMoyenne") {
        params["sampling size"] = 5;
        params["temperature initiale"] = 1000;
        params["taux de refroidissement"] = 0.7;
        params["temperature finale"] = 50;
    } else if (dataset_name == "FacilePetite") {
        params["sampling size"] = 10;
        params["temperature initiale"] = 600;
        params["taux de refroidissement"] = 0.9;
        params["temperature finale"] = 450;
    } else if (dataset_name == "MoyenneGrande") {
        params["sampling size"] = 5;
        params["temperature initiale"] = 1000;
        params["taux de refroidissement"] = 0.85;
        params["temperature finale"] = 50;
    } else if (dataset_name == "MoyenneMoyenne") {
        params["sampling size"] = 10;
        params["temperature initiale"] = 600;
        params["taux de refroidissement"] = 0.9;
        params["temperature finale"] = 50;
    } else if (dataset_name == "MoyennePetite") {
        params["sampling size"] = 10;
        params["temperature initiale"] = 1000;
        params["taux de refroidissement"] = 0.9;
        params["temperature finale"] = 450;
    }
    return params;
}


std::map<std::string, double> get_GA_parameters(std::string dataset_name) {
    std::map<std::string, double> params;
    if (dataset_name == "DifficileGrande") {
        params["generations count"] = 60;
        params["generation size"] = 70;
        params["mutation rate"] = 0.1;
    } else if (dataset_name == "DifficuleMoyenne") {
        params["generations count"] = 70;
        params["generation size"] = 100;
        params["mutation rate"] = 0.1;
    } else if (dataset_name == "DifficulePetite") {
        params["generations count"] = 60;
        params["generation size"] = 20;
        params["mutation rate"] = 0.1;
    } else if (dataset_name == "FacileGrande") {
        params["generations count"] = 1;
        params["generation size"] = 10;
        params["mutation rate"] = 0.05;
    } else if (dataset_name == "FacileMoyenne") {
        params["generations count"] = 10;
        params["generation size"] = 20;
        params["mutation rate"] = 0.1;
    } else if (dataset_name == "FacilePetite") {
        params["generations count"] = 10;
        params["generation size"] = 80;
        params["mutation rate"] = 0.05;
    } else if (dataset_name == "MoyenneGrande") {
        params["generations count"] = 10;
        params["generation size"] = 10;
        params["mutation rate"] = 0.05;
    } else if (dataset_name == "MoyenneMoyenne") {
        params["generations count"] = 70;
        params["generation size"] = 40;
        params["mutation rate"] = 0.1;
    } else if (dataset_name == "MoyennePetite") {
        params["generations count"] = 90;
        params["generation size"] = 40;
        params["mutation rate"] = 0.05;
    }
    return params;
}


std::vector<int> convertToNsolution(std::vector<int>& items, int nb_items) {
    std::vector<int> solution(nb_items, 0);
    for (int i : items) solution[i]++;
    return solution;
}

double calculate_total_weight(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values) {
    double w = 0.0f;
    for (int i = 0; i < solution.size(); ++i) w += solution[i] * weights[i];
    return w;
}

double calculate_total_values(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values) {
    double v = 0.0f;
    for (int i = 0; i < solution.size(); ++i) v += solution[i] * values[i];
    return v;
}

bool is_valid_solution(std::vector<int>& solution, std::vector<double>& weights, std::vector<double>& values, double sack_size) {
    double w = 0.0;
    for (int i = 0; i < solution.size(); ++i) w += weights[i] * solution[i];
    return w <= sack_size;
}

void generate_random_instance(int nb_items, std::vector<double>& items_weight, std::vector<double>& values, double min_item_weight, double min_item_value, double max_item_weight, double max_item_value) {
    items_weight.clear();
    values.clear();
    for (int i = 0; i < nb_items; ++i) {
        items_weight.push_back(min_item_weight + rand() % (int)(max_item_weight - min_item_weight));
        values.push_back(min_item_value + rand() % (int)(max_item_value - min_item_value));
    }
}

void read_data(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size) {
    std::ifstream in(file_name, std::ios::in);
    weights.clear();
    values.clear();
    if (!in.is_open()) return;
    std::string line;
    // comment lines
    std::getline(in, line);
    std::getline(in, line);
    std::getline(in, line);
    // items count
    std::string place_holder;
    int items_count;
    in >> place_holder >> items_count; in.ignore();
    std::getline(in, line);
    // sack_size
    in >> place_holder >> sack_size; in.ignore();
    std::getline(in, line);
    std::getline(in, line);
    // begin data
    std::getline(in, line);
    assert(line == "begin data ");
    // 
    for (int i = 0; i < items_count; ++i) {
        double w, v;
        in >> w >> v; in.ignore();
        weights.push_back(w);
        values.push_back(v);
    }
    in.close();
}

void get_noncomment_line(istream &in, string &line) {
    const string comm_s("[ \t]*(#.*)?");
    const regex  comm(comm_s);
    do getline(in, line); while (in.good() && regex_match(line, comm));
}

void get_noncomm_line_in_data(istream &in, string &line) {
    static const string warn_blank_in_data = "WARNING: read_ukp_instance: found a blank line inside data section.";
    const string comm_s("[ \t]*(#.*)?");
    const regex  comm(comm_s);
    getline(in, line);
    while (in.good() && regex_match(line, comm)) getline(in, line);
}

void read_wp(std::string item, double& w, double& p) {
    std::stringstream ss;
    ss << item;
    ss >> w;
    ss >> p;
}

void read_ukp_datset(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size) {
    const string n_line("n:.*");
    const string c_line("c:.*");
    const string begin_data_line("begin data.*");
    const regex  n_line_regex(n_line);
    const regex  c_line_regex(c_line);
    const regex  begin_data_regex(begin_data_line);
    
    std::ifstream in(file_name, std::ios::in);
    
    weights.clear();
    values.clear();
    if (!in.is_open()) {
        std::cout << "Couldn't open file " << file_name << std::endl;
    }

    string line;
    int n = 0, c = 0;
    do {
        getline(in, line);
        if (regex_match(line, n_line_regex)) {
            n = stoi(line.substr(2));
        }
        if (regex_match(line, c_line_regex)) {
            c = stoi(line.substr(2));
        }
    } while (in.good() && !regex_match(line, begin_data_regex));

    for (int i = 0; i < n && in.good(); ++i) {
        std::getline(in, line);
        double w, p;
        read_wp(line, w, p);
        weights.push_back(w);
        values.push_back(p);
    }

    sack_size = c;
}
