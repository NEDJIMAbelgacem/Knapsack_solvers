#include "itemslist.h"
#include "ui_itemslist.h"
#include <iostream>

ItemsList::ItemsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsList)
{
    ui->setupUi(this);
    this->items_table = this->ui->itemsTable;
    items_table->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    items_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectColumns);
    table_model = new ItemsListTableModel(this);
    items_table->setModel(table_model);

    QObject::connect(items_table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this, SLOT(itemsSelected(QItemSelection,QItemSelection)));
}

ItemsList::~ItemsList()
{
    delete ui;
}
