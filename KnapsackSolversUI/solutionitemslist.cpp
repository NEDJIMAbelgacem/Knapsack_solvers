#include "solutionitemslist.h"
#include "ui_solutionitemslist.h"

SolutionItemsList::SolutionItemsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolutionItemsList)
{
    ui->setupUi(this);
    this->items_table = this->ui->solutionItemsTable;
    items_table->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    items_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectColumns);
    table_model = new SolutionItemsListTableModel(this);
    items_table->setModel(table_model);

    QObject::connect(items_table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this, SLOT(itemsSelected(QItemSelection,QItemSelection)));
}

SolutionItemsList::~SolutionItemsList()
{
    delete ui;
}
