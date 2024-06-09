#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "Service.h"

class AdoptionListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AdoptionListModel(Service& service, QObject* parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


private:
    Service& service;
};
