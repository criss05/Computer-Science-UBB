#include "FilterModel.h"

bool FilterModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const{
    if (!this->show)
        return true;
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    QString constellation = sourceModel()->data(index).toString();

    if (constellation == QString::fromStdString(this->constellation))
        return true;
    return false;
}

void FilterModel::setFilter(bool active){
    this->show = active;
    this->invalidateFilter();
}

void FilterModel::UpdateModel(){
    model.UpdateModel();
}
