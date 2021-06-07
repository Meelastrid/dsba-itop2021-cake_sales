#include "./ui_mainwindow.h"
#include "addcake.h"
#include "cakecomposition.h"
#include "cakemodel.h"
#include "mainwindow.h"
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Data model
    proxyModel->setSourceModel(cakeModel);
    proxyModel->setDynamicSortFilter(false);

    // Set view for data model, hide composition column -
    // use it for composition window.
    ui->cakeTableView->setModel(proxyModel);
    ui->cakeTableView->setSortingEnabled(false);
    ui->cakeTableView->setColumnHidden(10, true);
    ui->cakeTableView->show();

    // Open Cake DB file menu item,
    // connect click signal with open file dialog function
    QAction * openDB = new QAction("Open cakes file", this);
    ui->menuFile->addAction(openDB);
    connect(openDB, SIGNAL(triggered()), this, SLOT(slotOpenDB()));

    // Open Save menu item,
    // connect click signal with save file dialog function
    QAction * save = new QAction("Save", this);
    ui->menuFile->addAction(save);
    connect(save, SIGNAL(triggered()), this, SLOT(slotSaveDB()));

    // Open Help menu item,
    // connect click signal with Help message
    QAction * help = new QAction("Help", this);
    ui->menuHelp->addAction(help);
    connect(help, SIGNAL(triggered()), this, SLOT(slotHelp()));

    // Open About menu item,
    // connect click signal with About message
    QAction * about = new QAction("About", this);
    ui->menuHelp->addAction(about);
    connect(about, SIGNAL(triggered()), this, SLOT(slotAbout()));

    // out stream
    QTextStream out(stdout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cakeAdded(Cake cake, int row)
{
    //restore original order
    this->proxyModel->setSortRole(Qt::InitialSortOrderRole);
    this->proxyModel->invalidate();

    std::map<int, int> ftc = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}, {6, 10}};
    QAbstractItemModel *model = ui->cakeTableView->model();

    // add item below selected item if any item is selected
    QTextStream out(stdout);
    out<< model->rowCount() << Qt::endl;
    out << row << Qt::endl;
    model->insertRow(row);
    out << row << Qt::endl;
    out<< model->rowCount() << Qt::endl;
    out  << Qt::endl;
    QModelIndex index = model->index(row, 0);
    model->setData(index, cake.name);
    index = model->index(row, 1);
    model->setData(index, cake.retail_price);
    index = model->index(row, 2);
    model->setData(index, cake.wholesale_price);
    index = model->index(row, 3);
    model->setData(index, cake.sold_retail);
    index = model->index(row, 4);
    model->setData(index, cake.sold_wholesale);
    index = model->index(row, 6);
    model->setData(index, cake.calories);
    index = model->index(row, 10);
    model->setData(index, cake.composition);

}

void MainWindow::on_addCakeButton_clicked()
{
    int row;
    QAbstractItemModel *model = ui->cakeTableView->model();
    QModelIndexList selection = ui->cakeTableView->selectionModel()->selection().indexes();

    if (selection.length() == 0)
        row = 0;
    else
        row = selection.at(0).row();
    AddCake *addcake = new AddCake(this, row);
    addcake->show();
}


void MainWindow::slotOpenDB()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Cake DB csv"), this->currentDB,
                                                    tr("Cake DB(*.csv)"));
    loadTextFile(fileName);
    this->currentDB = fileName;
}

void MainWindow::slotSaveDB()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open Cake DB csv"), this->currentDB,
                                                    tr("Cake DB(*.csv)"));
    saveTextFile(fileName);
    this->currentDB = fileName;
}

void MainWindow::slotHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("CakeSales Help");
    msgBox->setText(
                "Cake Sales Help.\n"
                "Choose a csv file to read your cakes database\n"
                "To add cake press Add cake button\n"
                "Have fun baking!\n"
                    );
    msgBox->show();
}
void MainWindow::slotAbout()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("About CakeSales");
    msgBox->setText("Cake Sales App.\nBake, sell and save your favourite cakes!\nCreated by student 108");
    msgBox->show();
}


void MainWindow::saveTextFile(QString fileName)
{
    QAbstractItemModel *model = ui->cakeTableView->model();
    std::map<int, int> ftc = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}, {6, 10}};
    QModelIndex index = model->index(0,0);
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::WriteOnly)) {

        QTextStream outf(&inputFile); // read to text stream
        for (int i = 0; i < model->rowCount() - 1; i++ ) {
            for (int j = 0; j < 7; j++ ) {
                index = model->index(i,ftc[j]);
                outf << model->data(index).toString();
                if (j < 6)
                {
                    outf << ";";
                }
            }
            outf << Qt::endl;

        }
    }
    inputFile.close();
}

void MainWindow::loadTextFile(QString fileName)
{

    QAbstractItemModel *model = ui->cakeTableView->model();
    model->removeRows(0,model->rowCount() - 1);
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly)) {

        int i = 0; // file line counter
        QTextStream in(&inputFile); // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(";", Qt::SkipEmptyParts);

            // map for file-to-column relation
            std::map<int, int> ftc = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}, {6, 10}};

            model->insertRow(i);
            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {

                QString value = lineToken.at(j);
                QModelIndex index = model->index(i,ftc[j]);
                model->setData(index, value);
            }
            // Update calculated fields
            for (int cell = 7; cell < 10; cell++)
            {
                QModelIndex in = model->index(i, cell);
                ui->cakeTableView->update(in);
            }
            i++;
        }
        inputFile.close();
    }
}


void MainWindow::on_deleteCakeButton_clicked()
{

    //restore original order
    this->proxyModel->setSortRole(Qt::InitialSortOrderRole);
    this->proxyModel->invalidate();

    QAbstractItemModel *model = ui->cakeTableView->model();
    QModelIndexList selection = ui->cakeTableView->selectionModel()->selection().indexes();

    // calculate number of rows in selection
    if (selection.count() > 0)
    {
    QSet<int> rows;
    for(int i=0; i< selection.count(); i++)
    {
        rows.insert(selection.at(i).row());
    }


    model->removeRows(selection.at(0).row(), rows.count());
    }
}


void MainWindow::on_showCompositionButton_clicked()
{

    QModelIndexList selection = ui->cakeTableView->selectionModel()->selection().indexes();
    QAbstractItemModel *compModel = ui->cakeTableView->model();

    if (selection.count() > 0)
    {
    int row = selection.at(0).row();

    CakeComposition *cakeComposition = new CakeComposition(this, compModel, row);
    cakeComposition->show();

    }

}

void MainWindow::on_sortNameButton_clicked()
{
       this->proxyModel->setSortRole(Qt::DisplayRole);
       ui->cakeTableView->sortByColumn(0, Qt::AscendingOrder);
}


void MainWindow::on_sortTotalIncomeButton_clicked()
{
       this->proxyModel->setSortRole(Qt::DisplayRole);
       ui->cakeTableView->sortByColumn(5, Qt::AscendingOrder);
}


void MainWindow::on_sortTotalKgSoldButton_clicked()
{
       this->proxyModel->setSortRole(Qt::DisplayRole);
       ui->cakeTableView->sortByColumn(9, Qt::AscendingOrder);

}


void MainWindow::on_showTop3MostCaloricButton_clicked()
{

}

