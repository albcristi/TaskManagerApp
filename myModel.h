#pragma once

#include <qabstractitemmodel.h>
#include "Repository.h"

class myModel : public QAbstractTableModel
{

	Repository* repo;

public:
	myModel(Repository* _repo,QObject *parent=0);

	int rowCount(const QModelIndex& index) const;

	int columnCount(const QModelIndex& index) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	QVariant data(const QModelIndex& index, int role) const;
	
	void signalRowAdded();

	void signalRowChanged();

	bool removeRow(int row, const QModelIndex& parent = QModelIndex());
	~myModel();
};
