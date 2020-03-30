#include "myModel.h"
#include <qcolor.h>
myModel::myModel(Repository* _repo,QObject *parent)
	: QAbstractTableModel(parent),repo(_repo)
{
}

int myModel::rowCount(const QModelIndex& index) const
{
	return this->repo->getSize();
}

int myModel::columnCount(const QModelIndex& index) const
{
	return 3;
}

QVariant myModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section)
			{
			case 0:
				return QString("Description");
			case 1:
				return QString("Status");
			case 2:
				return QString("Handler ID");
			default:
				break;
			}
		}
	}
	return QVariant();

}

QVariant myModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Task tsk = this->repo->getTasks()[row];
	if (role == Qt::DisplayRole) {
		switch (column)
		{
		case 0:
			return QString::fromStdString(tsk.getDescription());
		case 1:
			return QString::fromStdString(tsk.getStatus());
		case 2:
			return QString::number(tsk.getId());
		default:
			break;
		}
	}
	if (role == Qt::BackgroundRole) {
		if(row%2==0)
		   return QColor(Qt::green);
	}
	return QVariant();
}

void myModel::signalRowAdded()
{
	QAbstractItemModel::beginInsertRows(QModelIndex(), this->repo->getSize(), this->repo->getSize());
	QAbstractItemModel::endInsertRows();

}

void myModel::signalRowChanged()
{
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
}


bool myModel::removeRow(int row, const QModelIndex& parent)
{
	
	QAbstractItemModel::removeRow(row);
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
	return true;
}

myModel::~myModel()
{
}
