#include "MyModel.h"

int Model::rowCount(const QModelIndex& parent) const
{
    return service.GetStars().size();
}

int Model::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();

    Star star = service.GetStars()[row];

    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0:
            return QString::fromStdString(star.GetName());
        case 1:
            return QString::fromStdString(star.GetConstellation());
        case 2:
            return QString::number(star.GetRA());
        case 3:
            return QString::number(star.GetDec());
        case 4:
            return QString::number(star.GetDiameter());
        default:
            break;
        }
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString::fromStdString("Name");
            case 1:
                return QString::fromStdString("Constellation");
            case 2:
                return QString::fromStdString("RA");
            case 3:
                return QString::fromStdString("DEC");
            case 4:
                return QString::fromStdString("Diameter");
            default:
                break;
            }
        }
    }
    return QVariant();
}

void Model::UpdateModel(){
    this->beginResetModel();
    this->resetInternalData();
    this->endResetModel();
}
