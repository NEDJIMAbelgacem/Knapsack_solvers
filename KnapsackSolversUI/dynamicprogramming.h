#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <vector>

#include "itemslist.h"
#include "solutionitemslist.h"

class DynamicProgramming
{
public:
    QComboBox* dataSetCB = nullptr;
    ItemsList* dataTableWidget = nullptr;
    SolutionItemsList* solutionTableWidget = nullptr;
    QSpinBox* sackSizeSpinBox = nullptr;
    QLabel* totalWeightLabel = nullptr;
    QLabel* totalProfitLabel = nullptr;
    QLabel* executionTimeLabel = nullptr;
    QPushButton* executeAlgorithmBtn = nullptr;

    std::vector<int> solution;
public:
    DynamicProgramming();
    void loadDataSet(QString dataset_name);
    void executeAlgorithm();
    void init();
};

#endif // DYNAMICPROGRAMMING_H
