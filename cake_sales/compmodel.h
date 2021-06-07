#ifndef COMPMODEL_H
#define COMPMODEL_H

#include <QAbstractTableModel>

class CompModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CompModel(const QStringList &strings, QObject *parent = nullptr)
        : QAbstractListModel(parent), stringList(strings) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    QStringList stringList;
};

#endif // COMPMODEL_H
