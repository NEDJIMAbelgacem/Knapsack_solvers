#ifndef HYBRIDALGORITHM_H
#define HYBRIDALGORITHM_H

#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <vector>

#include "itemslist.h"
#include "solutionitemslist.h"

class HybridAlgorithm
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
    QSpinBox* populationCountSpinBox = nullptr;
    QSpinBox* generationsCountSpinBox = nullptr;
    QSpinBox* iterationsCountSpinBox = nullptr;
//    ItemsList* generationsEvolutionTableWidget = nullptr;

    std::vector<int> solution;
public:
    HybridAlgorithm();
    void loadDataSet(QString dataset_name);
    void executeAlgorithm();
    void init();
};

#endif // HYBRIDALGORITHM_H
