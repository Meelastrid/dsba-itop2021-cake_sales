#ifndef TOP3_H
#define TOP3_H

#include <QDialog>
#include <QVector>
#include "cakemodel.h"

namespace Ui {
class Top3;
}

class Top3 : public QDialog
{
    Q_OBJECT

public:
    explicit Top3(QWidget *parent = nullptr, QAbstractItemModel *cakeModel = nullptr, QVector<int> max3 = {});
    ~Top3();

private:
    Ui::Top3 *ui;
};

#endif // TOP3_H
