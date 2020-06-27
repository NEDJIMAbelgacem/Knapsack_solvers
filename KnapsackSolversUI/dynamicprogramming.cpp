#include "dynamicprogramming.h"
#include "mainwindow.h"

#include "utils.h"

#include <QDebug>
#include <iostream>
#include <stdio.h>
#include <chrono>

DynamicProgramming::DynamicProgramming()
{

}

void DynamicProgramming::loadDataSet(QString dataset_name) {
    dataTableWidget->clear();
    for (int i = 0; i < MainWindow::dataset_size[dataset_name] && i < 100; ++i) {
        double w = MainWindow::dataset_items_weights[dataset_name][i];
        double p = MainWindow::dataset_items_values[dataset_name][i];
        dataTableWidget->addItem(p, w);
    }
}

void DynamicProgramming::init() {
    QObject::connect(dataSetCB, &QComboBox::currentTextChanged, [&](const QString& text) {
        loadDataSet(text);
    });
    for (QString dataset : MainWindow::datasets_file_path.keys()) dataSetCB->addItem(dataset);
    QObject::connect(executeAlgorithmBtn, &QPushButton::clicked, [&](bool ) {
        executeAlgorithm();
    });
}

void DynamicProgramming::executeAlgorithm() {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    QString dataset_name = dataSetCB->currentText();
    if (MainWindow::dataset_size[dataset_name] > 50) {
        // errorr message here
        return;
    }
    double sack_size = sackSizeSpinBox->value();
    QString command = MainWindow::methods_executable_paths[QString("dynamic_programming")];
    command += QString(" 0 %1").arg(sack_size) + " " + MainWindow::datasets_file_path[dataset_name];
    qDebug() << command;
    std::vector<double> items_weight = MainWindow::dataset_items_weights[dataset_name];
    std::vector<double> items_values = MainWindow::dataset_items_values[dataset_name];
    start = std::chrono::system_clock::now();
    FILE* pipe = popen(command.toStdString().c_str(), "r");
    end = std::chrono::system_clock::now();
    int n, k;
    solution.clear();
    solutionTableWidget->clear();
    fscanf(pipe, "%d", &n);
    for (int i = 0; i < n; ++i) {
        fscanf(pipe, "%d", &k);
        solution.push_back(k);
        solutionTableWidget->addItem(items_values[i], items_weight[i], k);
    }
    double time_taken;
    fscanf(pipe, "%lf", &time_taken);
    fclose(pipe);

    double solutions_weight = calculate_total_weight(solution, items_weight, items_values);
    double solutions_profit = calculate_total_values(solution, items_weight, items_values);
    totalWeightLabel->setText(QString("%1").arg((long long)solutions_weight));
    totalProfitLabel->setText(QString("%1").arg((long long)solutions_profit));
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    executionTimeLabel->setText(QString("%1 seconds").arg(time_taken));
}
