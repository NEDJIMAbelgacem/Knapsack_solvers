#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QComboBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <vector>

#include "itemslist.h"
#include "solutionitemslist.h"

class GeneticAlgorithm
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
//    ItemsList* generationsEvolutionTableWidget = nullptr;

    std::vector<int> solution;
public:
    GeneticAlgorithm();
    void loadDataSet(QString dataset_name);
    void executeAlgorithm();
    void init();
};

#endif // GENETICALGORITHM_H
