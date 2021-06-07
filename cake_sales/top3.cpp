#include "top3.h"
#include "ui_top3.h"

Top3::Top3(QWidget *parent, QAbstractItemModel *cakeModel, QVector<int> max3) :
    QDialog(parent),
    ui(new Ui::Top3)
{
    ui->setupUi(this);

    //QModelIndex index = cakeModel->index(row, 10);
    //QVariant comp = cakeModel->data(index);
    //QStringList strings = comp.toString().split(",");
    //CompModel *compModel = new CompModel(strings, this);
    //ui->compListView->setModel(compModel);
    //ui->compListView->show();
}

Top3::~Top3()
{
    delete ui;
}
