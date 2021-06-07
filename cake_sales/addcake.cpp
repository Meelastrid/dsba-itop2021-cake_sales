#include "addcake.h"
#include "ui_addcake.h"
#include "cakemodel.h"


AddCake::AddCake(QWidget *parent, int row) :
    QDialog(parent),
    ui(new Ui::AddCake)
{
    ui->setupUi(this);
    connect(this, SIGNAL(buttonBox_accepted(Cake,int)), parent, SLOT(on_cakeAdded(Cake,int)));
    this->row = row;

}

AddCake::~AddCake()
{
    delete ui;
}

void AddCake::on_buttonBox_accepted()
{


            Cake new_cake;

            new_cake.name = ui->nameEdit->text();
            new_cake.retail_price = ui->retailEdit->text().toInt();
            new_cake.wholesale_price = ui->wholesaleEdit->text().toInt();
            new_cake.sold_retail = ui->soldREdit->text().toInt();
            new_cake.sold_wholesale = ui->soldWEdit->text().toInt();
            new_cake.calories = ui->caloricEdit->text().toInt();
            QStringList comp = ui->compEdit->text().split(",", Qt::SkipEmptyParts);
            new_cake.composition = comp;
            emit buttonBox_accepted(new_cake, this->row);


}

