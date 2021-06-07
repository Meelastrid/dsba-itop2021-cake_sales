#ifndef ADDCAKE_H
#define ADDCAKE_H


#include <QDialog>
#include <cake.h>

namespace Ui {
class AddCake;
}

class AddCake : public QDialog
{
    Q_OBJECT

public:
    explicit AddCake(QWidget *parent = nullptr, int row = 0);
    ~AddCake();


signals:
    void buttonBox_accepted(Cake cake, int row);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddCake *ui;
    int row;
};

#endif // ADDCAKE_H
