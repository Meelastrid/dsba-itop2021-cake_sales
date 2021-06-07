#ifndef CAKEMODEL_H
#define CAKEMODEL_H


#include <QAbstractTableModel>
#include <QString>
#include <cake.h>

const int COLS= 3;
const int ROWS= 2;


class CakeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CakeModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QVector<Cake> cakes;   // Stores cakes


};

#endif // CAKEMODEL_H
