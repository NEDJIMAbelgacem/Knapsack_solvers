#ifndef SOLUTIONITEMSLIST_H
#define SOLUTIONITEMSLIST_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QHeaderView>
#include <iostream>

namespace Ui {
class SolutionItemsList;
}

class SolutionItemsListTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QVector<int> items_values;
    QVector<int> items_weights;
    QVector<int> items_repetition;
public:
    SolutionItemsListTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {

    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return 3;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return items_values.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            switch (index.row()) {
            case 0: return QString("%1").arg(items_values[index.column()]);
            case 1: return QString("%1").arg(items_weights[index.column()]);
            case 2: return QString("%1").arg(items_repetition[index.column()]);
                break;
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Vertical) {
                if (section == 0) return QString("profit : ");
                if (section == 1) return QString("weight : ");
                if (section == 2) return QString("repetition : ");
            }
            if (orientation == Qt::Horizontal) {
                return QString("%1").arg(section);
            }
        }
        return QVariant();
    }

    void addItem(int value, int weight, int repetition) {
        items_values.push_back(value);
        items_weights.push_back(weight);
        items_repetition.push_front(repetition);
        emit layoutChanged();
    }

    QVector<QPair<QPair<int, int>, int>> getItems() {
        QVector<QPair<QPair<int, int>, int>> items;
        for (int i = 0; i < items_values.size(); ++i) {
            items.append(QPair<QPair<int, int>, int>({items_values[i], items_weights[i]}, items_repetition[i]));
        }
        return items;
    }

    void clear() {
        items_values.clear();
        items_weights.clear();
        items_repetition.clear();
    }
};

class SolutionItemsList : public QWidget
{
    Q_OBJECT
public:
    explicit SolutionItemsList(QWidget *parent = 0);
    ~SolutionItemsList();
    void addItem(int value, int weight, int repetition) {
        table_model->addItem(value, weight, repetition);
    }

    QVector<QPair<QPair<int, int>, int>> getItems() {
        return table_model->getItems();
    }

    int itemsCount() { return table_model->columnCount(); }

    void clear() {
        table_model->clear();
    }

    void deleteItems(QSet<int> items_indexes) {
        QVector<QPair<QPair<int, int>, int>> items = getItems();
        clear();
        for (int i = 0; i < items.size(); ++i) {
            if (!items_indexes.contains(i)) {
                addItem(items[i].first.first, items[i].first.second, items[i].second);
            }
        }
    }

private:
    Ui::SolutionItemsList *ui = nullptr;
    QTableView* items_table = nullptr;
    SolutionItemsListTableModel* table_model = nullptr;
public slots:
    void itemsSelected(QVector<int> items) {
        QItemSelection items_selection;
        items_table->selectionModel()->clearSelection();
        for (int i : items) {
            items_table->selectColumn(i);
            items_selection.merge(items_table->selectionModel()->selection(), QItemSelectionModel::Select);
        }
        items_table->selectionModel()->select(items_selection, QItemSelectionModel::Select);
    }
    void itemsSelected(const QItemSelection &selected, const QItemSelection &deselected) {
        QSet<int> selected_items_indexes_set;
        QModelIndexList items_list = items_table->selectionModel()->selectedIndexes();
        for (QModelIndex m : items_list) {
            selected_items_indexes_set.insert(m.column());
        }
        QVector<int> selected_items_indexes;
        for (int i : selected_items_indexes_set) selected_items_indexes.push_back(i);
        emit itemsSelectedSignal(selected_items_indexes);
    }
signals:
    void itemsSelectedSignal(QVector<int> items);
};


#endif // SOLUTIONITEMSLIST_H
