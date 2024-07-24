#include "WriterModel.h"

int WriterModel::rowCount(const QModelIndex& parent) const
{
    return repo.GetIdeas().size();
}

int WriterModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant WriterModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();
	Idea idea = repo.GetIdeas()[row];
	if (role == Qt::DisplayRole) {
		switch (col) {
		case 0:
			return QString::fromStdString(idea.GetDescription());
		case 1:
			return QString::fromStdString(idea.GetStatus());
		case 2:
			return QString::fromStdString(idea.GetCreator());
		case 3:
			return QString::number(idea.GetAct());
		default:
			break;
		}
	}
    return QVariant();
}

QVariant WriterModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole) {
        if(orientation==Qt::Horizontal){
			switch(section){
				case 0:
					return "Description";
				case 1:
					return "Status";
				case 2:
					return "Creator";
				case 3:
					return "Act";
				default:
					break;
			}
		}
    }
    return QVariant();
}

void WriterModel::update(){
	this->beginResetModel();
	this->resetInternalData();
	this->endResetModel();
}
