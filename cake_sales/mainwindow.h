#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cake.h>
#include "cakemodel.h"
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotOpenDB();
    void slotSaveDB();
    void slotAbout();
    void slotHelp();
    void on_cakeAdded(Cake cake, int row);
    void on_addCakeButton_clicked();
    void on_deleteCakeButton_clicked();

    void on_showCompositionButton_clicked();

    void on_sortNameButton_clicked();

    void on_sortTotalIncomeButton_clicked();

    void on_sortTotalKgSoldButton_clicked();

    void on_showTop3MostCaloricButton_clicked();

private:
    Ui::MainWindow *ui;
    void loadTextFile(QString fileName);
    void saveTextFile(QString fileName);
    QString currentDB;
    // Data model
    CakeModel *cakeModel = new CakeModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
};
#endif // MAINWINDOW_H
