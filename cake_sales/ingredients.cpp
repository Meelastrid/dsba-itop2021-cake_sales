#include "ingredients.h"
#include "ui_ingredients.h"
#include "compmodel.h"
#include <QVector>
#include <QStringListModel>

    // Get ingredients vector "vec" as input
Ingredients::Ingredients(QWidget *parent, QVector<QString> vec) :
    QDialog(parent),
    ui(new Ui::Ingredients)
{
    ui->setupUi(this);

    //Sort vector
    std::sort( vec.begin(), vec.end() );
    //Get unique values from vector, then erase duplicates
    vec.erase( std::unique( vec.begin(), vec.end() ), vec.end() );
    //Create QStringListModel from this vector and show the window
    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(vec)));
    ui->listView->show();
}

Ingredients::~Ingredients()
{
    delete ui;
}
