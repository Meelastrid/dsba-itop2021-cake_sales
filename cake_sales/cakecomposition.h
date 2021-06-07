#ifndef CAKECOMPOSITION_H
#define CAKECOMPOSITION_H

#include <QDialog>
#include "cakemodel.h"

namespace Ui {
class CakeComposition;
}

class CakeComposition : public QDialog
{
    Q_OBJECT

public:
    explicit CakeComposition(QWidget *parent = nullptr, QAbstractItemModel *cakeModel = nullptr, int row = -1);
    ~CakeComposition();

private:
    Ui::CakeComposition *ui;
};

#endif // CAKECOMPOSITION_H
