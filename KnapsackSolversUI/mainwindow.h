#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QUrl>
#include <vector>

#include "dynamicprogramming.h"
#include "branchandbound.h"
#include "heuristics.h"
#include "geneticalgorithm.h"
#include "simulatedannealing.h"
#include "hybridalgorithm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    BranchAndBound* branchAndBound = nullptr;
    DynamicProgramming* dynamicProgramming = nullptr;
    Heuristics* heuristics = nullptr;
    GeneticAlgorithm* geneticAlgorithm = nullptr;
    SimulatedAnnealing* simulatedAnnealing = nullptr;
    HybridAlgorithm* hybridAlgorithm = nullptr;

public:
    static QString executables_path;
    static QMap<QString, QString> methods_executable_paths;
    static QString datasets_path;
    static QMap<QString, QString> datasets_file_path;
    static QMap<QString, int> dataset_size;
    static QMap<QString, std::vector<double>> dataset_items_weights;
    static QMap<QString, std::vector<double>> dataset_items_values;
    static QMap<QString, double> dataset_cost;
    static void loadDataSets();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
