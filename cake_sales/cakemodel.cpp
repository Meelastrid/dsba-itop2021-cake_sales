#include "cakemodel.h"
#include <QFont>
#include <QBrush>
#include <QString>
#include <QVector>

CakeModel::CakeModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CakeModel::rowCount(const QModelIndex & /*parent*/) const
{
    return cakes.length() + 1;
}

int CakeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 11;
}

bool CakeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    //delete only if selection contains all valid rows
    if (position + rows <= cakes.length())
    {
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    cakes.erase(cakes.begin() + position, cakes.begin() + position + rows);
    endRemoveRows();
    }
    //emit layoutChanged();
    return true;
}
bool CakeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (position >= 0 && position + rows <= cakes.length() +1)
    {
    beginInsertRows(QModelIndex(), position, position+rows-1);
    Cake new_cake;
    cakes.insert(position,new_cake);
    endInsertRows();
    }
    //emit layoutChanged();
    return true;
}


QVariant CakeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Cake");
        case 1:
            return QString("Retail price per kg");
        case 2:
            return QString("Wholesale price per kg");
        case 3:
            return QString("Sold (retail)");
        case 4:
            return QString("Sold (Wholesale)");
        case 5:
            return QString("Sold (Total)");
        case 6:
            return QString("Calories per 100g");
        case 7:
            return QString("Retail income");
        case 8:
            return QString("Wholesale income");
        case 9:
            return QString("Total income");
        }
    }
    return QVariant();
}


bool CakeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    emit dataChanged(index, index);
    Cake cur_cake = cakes.at(index.row());
    if (index.column() == 0)
        cur_cake.name = value.toString();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 1)
        cur_cake.retail_price = value.toInt();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 2)
        cur_cake.wholesale_price = value.toInt();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 3)
        cur_cake.sold_retail = value.toInt();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 4)
        cur_cake.sold_wholesale = value.toInt();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 6)
        cur_cake.calories = value.toInt();
    cakes.replace(index.row(), cur_cake);
    if (index.column() == 10)
    {
        QStringList comp = value.toString().split(",", Qt::SkipEmptyParts);
        cur_cake.composition = comp;
        cakes.replace(index.row(), cur_cake);
    }

    emit dataChanged(index, index);
    return true;
}

QVariant CakeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() > cakes.length() - 1)
    {
        return QVariant();
    }
    if (cakes.length() == 0)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        if (index.row() >= 0 and index.row() < cakes.length())
        {
            Cake cake = cakes.at(index.row());

            if (!index.isValid())
                return QVariant();
            if (index.column() == 0)
                return cake.name;
            if (index.column() == 1)
                return cake.retail_price;
            if (index.column() == 2)
                return cake.wholesale_price;
            if (index.column() == 3)
                return cake.sold_retail;
            if (index.column() == 4)
                return cake.sold_wholesale;
            if (index.column() == 5)
                return cake.sold_retail + cake.sold_wholesale;
            if (index.column() == 6)
                return cake.calories;
            if (index.column() == 7)
                return cake.retail_price * cake.sold_retail;
            if (index.column() == 8)
                return cake.wholesale_price * cake.sold_wholesale;
            if (index.column() == 9)
                return (cake.retail_price * cake.sold_retail) + (cake.wholesale_price * cake.sold_wholesale);
            if (index.column() == 10)
                return cake.composition.join(",");
        }

    }
    return QVariant();
}

