#ifndef HEURISTICS_H
#define HEURISTICS_H

#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <vector>

#include "itemslist.h"
#include "solutionitemslist.h"

class Heuristics
{
public:
    QComboBox* dataSetCB = nullptr;
    QComboBox* methodCB = nullptr;
    ItemsList* dataTableWidget = nullptr;
    SolutionItemsList* solutionTableWidget = nullptr;
    QSpinBox* sackSizeSpinBox = nullptr;
    QLabel* totalWeightLabel = nullptr;
    QLabel* totalProfitLabel = nullptr;
    QLabel* executionTimeLabel = nullptr;
    QPushButton* executeAlgorithmBtn = nullptr;

    std::vector<int> solution;
    int method = 0;
public:
    Heuristics();
    void loadDataSet(QString dataset_name);
    void executeAlgorithm();
    void init();
};
#endif // HEURISTICS_H
