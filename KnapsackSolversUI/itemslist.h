#ifndef ITEMSLIST_H
#define ITEMSLIST_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QHeaderView>
#include <iostream>

namespace Ui {
class ItemsList;
}

class ItemsListTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QVector<int> items_values;
    QVector<int> items_weights;
    QVector<QString> row_headers;
public:
    ItemsListTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {
        row_headers.push_back("profit : ");
        row_headers.push_back("weight : ");
    }

    void setRowHeader(int i, const QString& str) {
        if (i >= row_headers.size()) return;
        row_headers[i] = str;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return 2;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return items_values.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            switch (index.row()) {
            case 0: return QString("%1").arg(items_values[index.column()]);
            case 1: return QString("%1").arg(items_weights[index.column()]);
                break;
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Vertical) {
                if (section <= 1) return row_headers[section];
            }
            if (orientation == Qt::Horizontal) {
                return QString("%1").arg(section);
            }
        }
        return QVariant();
    }

    void addItem(int value, int weight) {
        items_values.push_back(value);
        items_weights.push_back(weight);
        emit layoutChanged();
    }

    QVector<QPair<int, int>> getItems() {
        QVector<QPair<int, int>> items;
        for (int i = 0; i < items_values.size(); ++i) {
            items.append({items_values[i], items_weights[i]});
        }
        return items;
    }

    void clear() {
        items_values.clear();
        items_weights.clear();
    }
};

class ItemsList : public QWidget
{
    Q_OBJECT
public:
    explicit ItemsList(QWidget *parent = 0);
    ~ItemsList();
    void addItem(int value, int weight) {
        table_model->addItem(value, weight);
    }

    void setRowHeader(int i, const QString& str) {
        table_model->setRowHeader(i, str);
    }

    int itemsCount() { return table_model->getItems().size(); }

    QVector<QPair<int, int>> getItems() {
        return table_model->getItems();
    }

    void clear() {
        table_model->clear();
    }

    void deleteItems(QSet<int> items_indexes) {
        QVector<QPair<int, int>> items = getItems();
        clear();
        for (int i = 0; i < items.size(); ++i) {
            if (!items_indexes.contains(i)) {
                addItem(items[i].first, items[i].second);
            }
        }
    }

private:
    Ui::ItemsList *ui = nullptr;
    QTableView* items_table = nullptr;
    ItemsListTableModel* table_model = nullptr;
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

#endif // ITEMSLIST_H
