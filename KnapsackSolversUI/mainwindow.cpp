#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>

#include <QDebug>
#include <QDir>
#include <QFileDialog>

void read_wp(std::string item, double& w, double& p) {
    std::stringstream ss;
    ss << item;
    ss >> w;
    ss >> p;
}

void read_ukp_datset(std::string file_name, std::vector<double>& weights, std::vector<double>& values, double& sack_size) {
    using namespace std;
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


QString MainWindow::executables_path = "/home/nedjima/Desktop/Knapsack_solvers/build/bin";
//QString MainWindow::datasets_path = "/home/nedjima/Desktop/Knapsack_solvers/data/ukp";
QString MainWindow::datasets_path = "/home/nedjima/Desktop/Knapsack_solvers/datasets";

QMap<QString, QString> MainWindow::methods_executable_paths;
QMap<QString, QString> MainWindow::datasets_file_path;

QMap<QString, int> MainWindow::dataset_size;
QMap<QString, std::vector<double>> MainWindow::dataset_items_weights;
QMap<QString, std::vector<double>> MainWindow::dataset_items_values;
QMap<QString, double> MainWindow::dataset_cost;

void MainWindow::loadDataSets() {
    QDir directory(datasets_path);
    QStringList datasets_filenames = directory.entryList();
    for (QString s : datasets_filenames) {
        if (s == "." || s == "..") continue;
        std::vector<double> weights;
        std::vector<double> values;
        double sack_size;
        std::string file_name = datasets_path.toStdString();
        file_name.push_back('/');
        file_name += s.toStdString();
        read_ukp_datset(file_name, weights, values, sack_size);

        datasets_file_path[s] = QString::fromStdString(file_name);
        dataset_size[s] = weights.size();
        dataset_items_weights[s] = weights;
        dataset_items_values[s] = values;
        dataset_cost[s] = sack_size;
    }

    methods_executable_paths[QString("dynamic_programming")] = executables_path + "/" + "dynamic_programming";
    methods_executable_paths[QString("branch_and_bound")] = executables_path + "/" + "branch_and_bound";
    methods_executable_paths[QString("heuristics")] = executables_path + "/" + "heuristics";
    methods_executable_paths[QString("genetic_algorithm")] = executables_path + "/" + "genetic_algorithm";
    methods_executable_paths[QString("simulated_annealing")] = executables_path + "/" + "simulated_annealing";
    methods_executable_paths[QString("hybrid_algorithm")] = executables_path + "/" + "hybrid_algorithm";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadDataSets();
    ui->setupUi(this);

    dynamicProgramming = new DynamicProgramming;
    dynamicProgramming->dataSetCB = ui->DPDataSetComboBox;
    dynamicProgramming->dataTableWidget = ui->DPDataTable;
    dynamicProgramming->sackSizeSpinBox = ui->DPSackSizeSpinBox;
    dynamicProgramming->solutionTableWidget = ui->DPSolutionTable;
    dynamicProgramming->totalProfitLabel = ui->DPTotalProfitLabel;
    dynamicProgramming->totalWeightLabel = ui->DPTotalWeightLabel;
    dynamicProgramming->executionTimeLabel = ui->DPExecutionTimeLabel;
    dynamicProgramming->executeAlgorithmBtn = ui->DPExecuteAlgorithmBtn;
    dynamicProgramming->init();

    branchAndBound = new BranchAndBound;
    branchAndBound->dataSetCB = ui->BBDataSetComboBox;
    branchAndBound->dataTableWidget = ui->BBDataTable;
    branchAndBound->sackSizeSpinBox = ui->BBSackSizeSpinBox;
    branchAndBound->solutionTableWidget = ui->BBSolutionTable;
    branchAndBound->totalProfitLabel = ui->BBTotalProfitLabel;
    branchAndBound->totalWeightLabel = ui->BBTotalWeightLabel;
    branchAndBound->executionTimeLabel = ui->BBExecutionTimeLabel;
    branchAndBound->executeAlgorithmBtn = ui->BBExecuteAlgorithmBtn;
    branchAndBound->init();

    heuristics = new Heuristics;
    heuristics->dataSetCB = ui->HDataSetComboBox;
    heuristics->dataTableWidget = ui->HDataTable;
    heuristics->sackSizeSpinBox = ui->HSackSizeSpinBox;
    heuristics->solutionTableWidget = ui->HSolutionTable;
    heuristics->totalProfitLabel = ui->HTotalProfitLabel;
    heuristics->totalWeightLabel = ui->HTotalWeightLabel;
    heuristics->executionTimeLabel = ui->HExecutionTimeLabel;
    heuristics->executeAlgorithmBtn = ui->HExecuteAlgorithmBtn;
    heuristics->methodCB = ui->HMethodCB;
    heuristics->init();

    geneticAlgorithm = new GeneticAlgorithm;
    geneticAlgorithm->dataSetCB = ui->GADataSetComboBox;
    geneticAlgorithm->dataTableWidget = ui->GADataTable;
    geneticAlgorithm->sackSizeSpinBox = ui->GASackSizeSpinBox;
    geneticAlgorithm->solutionTableWidget = ui->GASolutionTable;
    geneticAlgorithm->totalProfitLabel = ui->GATotalProfitLabel;
    geneticAlgorithm->totalWeightLabel = ui->GATotalWeightLabel;
    geneticAlgorithm->executionTimeLabel = ui->GAExecutionTimeLabel;
    geneticAlgorithm->executeAlgorithmBtn = ui->GAExecuteAlgorithmBtn;
    geneticAlgorithm->populationCountSpinBox = ui->GAPopulationCount;
    geneticAlgorithm->generationsCountSpinBox = ui->GAGenerationsCount;
//    geneticAlgorithm->generationsEvolutionTableWidget = ui->GAGenerationsEvolutionTableWidget;
    geneticAlgorithm->init();

    simulatedAnnealing = new SimulatedAnnealing;
    simulatedAnnealing->dataSetCB = ui->SADataSetComboBox;
    simulatedAnnealing->dataTableWidget = ui->SADataTable;
    simulatedAnnealing->sackSizeSpinBox = ui->SASackSizeSpinBox;
    simulatedAnnealing->solutionTableWidget = ui->SASolutionTable;
    simulatedAnnealing->totalProfitLabel = ui->SATotalProfitLabel;
    simulatedAnnealing->totalWeightLabel = ui->SATotalWeightLabel;
    simulatedAnnealing->executionTimeLabel = ui->SAExecutionTimeLabel;
    simulatedAnnealing->executeAlgorithmBtn = ui->SAExecuteAlgorithmBtn;
    simulatedAnnealing->iterationsCountSpinBox = ui->SAIterationsCountSpinBox;
    simulatedAnnealing->init();

    hybridAlgorithm = new HybridAlgorithm;
    hybridAlgorithm->dataSetCB = ui->HADataSetComboBox;
    hybridAlgorithm->dataTableWidget = ui->HADataTable;
    hybridAlgorithm->sackSizeSpinBox = ui->HASackSizeSpinBox;
    hybridAlgorithm->solutionTableWidget = ui->HASolutionTable;
    hybridAlgorithm->totalProfitLabel = ui->HATotalProfitLabel;
    hybridAlgorithm->totalWeightLabel = ui->HATotalWeightLabel;
    hybridAlgorithm->executionTimeLabel = ui->HAExecutionTimeLabel;
    hybridAlgorithm->executeAlgorithmBtn = ui->HAExecuteAlgorithmBtn;
    hybridAlgorithm->populationCountSpinBox = ui->HAPopulationCount;
    hybridAlgorithm->generationsCountSpinBox = ui->HAGenerationsCount;
    hybridAlgorithm->iterationsCountSpinBox = ui->HAIterationsCountSpinBox;
    hybridAlgorithm->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

