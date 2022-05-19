#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QTime>


struct view_data{
    QString title;
    QString time_begin;
    QString time_end;
    bool check;
};

class model : public QAbstractTableModel
{
public:
    model(const QVector<view_data> & raws, QObject *parent = nullptr);

    int list_size();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order);
private:
    QVector<view_data> list;
};

#endif // MODEL_H
