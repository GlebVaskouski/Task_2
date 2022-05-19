#include "model.h"

#include <QColor>
#include <QBrush>

model::model(const QVector<view_data> & rows, QObject *parent) :
    QAbstractTableModel(parent), list(rows) {}

int model::list_size() {
    return list.size();
}

bool model::insertRows(int position, int rows, const QModelIndex &)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    view_data buffer{"", QTime::currentTime().toString("hh:mm A"), QTime::currentTime().toString("hh:mm A"), false};
    list.push_back(buffer);

    endInsertRows();
    return true;
}

int model::rowCount(const QModelIndex &) const{
    return list.size();
};

int model::columnCount(const QModelIndex &) const{
    return 3;
};

QVariant model::data(const QModelIndex &index, int role) const{
    if(index.isValid() && index.row() < list.size() && index.column() == 0 && role == Qt::DisplayRole){
        return list.at(index.row()).title;
    }
    if(index.isValid() && index.row() < list.size() && index.column() == 1 && role == Qt::DisplayRole){
        return list.at(index.row()).time_begin;
    }
    if(index.isValid() && index.row() < list.size() && index.column() == 2 && role == Qt::DisplayRole){
        return list.at(index.row()).time_end;
    }
    if(index.isValid() && index.row() < list.size() && index.column() == 0 && role == Qt::CheckStateRole){
        if (list.at(index.row()).check) {
            return Qt::Checked;
        } else {
        return Qt::Unchecked;
        }
    }
    if(index.isValid() && index.row() < list.size()
                && list.at(index.row()).check
                && role == Qt::BackgroundRole){
            return QColor(Qt::green);
        }
    return QVariant();
};

bool model::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role == Qt::EditRole) {
            if (index.isValid()){
                if(index.column() == 0){
            list[index.row()].title = value.toString();
                }
                if(index.column() == 1){
            list[index.row()].time_begin = value.toTime().toString("hh:mm A");
                }
                if(index.column() == 2){
            list[index.row()].time_end = value.toTime().toString("hh:mm A");
                }
            emit dataChanged(index, index);
            return true;
        }
    }
    if(role == Qt::CheckStateRole){
        if (index.isValid()){
            if(value == Qt::Checked){
        list[index.row()].check = true;
            }
            if(value == Qt::Unchecked){
        list[index.row()].check = false;
            }
        emit dataChanged(index, index);
        return true;
        }
    }
        return false;
};

QVariant model::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role != Qt::DisplayRole) {
        return QVariant();
    } else if(section == 0 && orientation == Qt::Horizontal) {
        return QString("Title");
    } else if(section == 1 && orientation == Qt::Horizontal) {
        return QString("Begin Time");
    }else if(section == 2 && orientation == Qt::Horizontal) {
        return QString("End Time");
    }
    return QVariant();
};

Qt::ItemFlags model::flags(const QModelIndex &index) const{
    if(index.column() == 0) {
        return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    }
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
};

void model::sort(int column, Qt::SortOrder order){
    if(order == Qt::AscendingOrder){
        switch(column){
        case 0 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check){
                return lhs.check > rhs.check;
            } else {
            return lhs.title > rhs.title;
            }
        });
        break;
        };
        case 1 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check) {
                return lhs.check > rhs.check;
            } else {
            return lhs.time_begin > rhs.time_begin;
            }
        });
        break;
        }
        case 2 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check){
                return lhs.check > rhs.check;
                } else {
            return lhs.time_end > rhs.time_end;
            }
        });
        break;
        }
        default : break;
        }
    } else {
        switch(column){
        case 0 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check) {
                return lhs.check > rhs.check;
                } else {
            return lhs.title < rhs.title;
            }
        });
        break;
        }
        case 1 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check) {
                return lhs.check > rhs.check;
                } else {
            return lhs.time_begin < rhs.time_begin;
            }
        });
        break;
        }
        case 2 : {
        std::sort(list.begin(), list.end(), [&](const view_data& lhs, const view_data& rhs){
            if(lhs.check != rhs.check){
                return lhs.check > rhs.check;
                } else {
            return lhs.time_end < rhs.time_end;
            }
        });
        break;
        }
        }
    }
    emit dataChanged(index(0, 0), index(list.size(), 3));
}
