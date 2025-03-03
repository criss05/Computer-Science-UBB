#pragma once
#include <vector>
#include "Repo.h"
#include <QAbstractTableModel>

class WriterModel : public QAbstractTableModel{
private:
	Repo& repo;
public:
	WriterModel(Repo& repo) : repo(repo) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void update();
};
