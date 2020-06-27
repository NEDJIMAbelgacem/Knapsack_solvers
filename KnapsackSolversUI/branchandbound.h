#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H
#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <vector>

#include "itemslist.h"
#include "solutionitemslist.h"

class BranchAndBound
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
    BranchAndBound();
    void loadDataSet(QString dataset_name);
    void executeAlgorithm();
    void init();
};

#endif // BRANCHANDBOUND_H
