#ifndef INGREDIENTS_H
#define INGREDIENTS_H
#include "compmodel.h"

#include <QDialog>
#include <QVector>

namespace Ui {
class Ingredients;
}

class Ingredients : public QDialog
{
    Q_OBJECT

public:
    // Get ingredients vector "vec" as input
    explicit Ingredients(QWidget *parent = nullptr, QVector<QString> vec = {});
    ~Ingredients();

private:
    Ui::Ingredients *ui;
};

#endif // INGREDIENTS_H
