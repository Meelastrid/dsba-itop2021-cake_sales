#include "compmodel.h"

int CompModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant CompModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
}


QVariant CompModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Composition").arg(section);
    else
        return QStringLiteral("Composition").arg(section);
}
