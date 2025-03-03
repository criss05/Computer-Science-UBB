#include "AdoptionListModel.h"

AdoptionListModel::AdoptionListModel(Service& service, QObject* parent)
    : QAbstractTableModel(parent), service(service)
{}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString{ "Breed" };
        case 1:
            return QString{ "Name" };
        case 2:
            return QString{ "Age" };
        case 3:
            return QString{ "Photograph"};
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int AdoptionListModel::rowCount(const QModelIndex& parent) const
{
    return service.GetSizeOfAdoptionList();
}

int AdoptionListModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant AdoptionListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();
    const auto& adoption_list = service.GetPetsFromAdoptionList();

    if (row >= adoption_list.size() || row < 0)
        return QVariant();

    const Pet& pet = adoption_list[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {

        switch (column) {
        case 0:
            return QString::fromStdString(pet.GetBreed());
        case 1:
            return QString::fromStdString(pet.GetName());
        case 2:
            return QString::number(pet.GetAge());
        case 3:
            return QString::fromStdString(pet.GetPhotograph());
        default:
            return QVariant();
        }
    }
    return QVariant{};
}

