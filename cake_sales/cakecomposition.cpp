#include "cakecomposition.h"
#include "ui_cakecomposition.h"
#include "compmodel.h"

CakeComposition::CakeComposition(QWidget *parent, QAbstractItemModel *cakeModel, int row) :
    QDialog(parent),
    ui(new Ui::CakeComposition)
{
    ui->setupUi(this);

    QModelIndex index = cakeModel->index(row, 10);
    QVariant comp = cakeModel->data(index);
    QStringList strings = comp.toString().split(",");
    CompModel *compModel = new CompModel(strings, this);
    ui->compListView->setModel(compModel);
    ui->compListView->show();
}

CakeComposition::~CakeComposition()
{
    delete ui;
}
