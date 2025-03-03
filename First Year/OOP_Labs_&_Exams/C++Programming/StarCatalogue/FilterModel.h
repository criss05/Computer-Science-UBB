#pragma once
#include <QSortFilterProxyModel>
#include "MyModel.h"

class FilterModel : public QSortFilterProxyModel {
private:
	bool show;
	std::string constellation;
	Model& model;

public:
	FilterModel(Model& model, std::string  cts) : model(model), constellation(cts), show(false) {}

	bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
	void setFilter(bool active);
	void UpdateModel();
};
