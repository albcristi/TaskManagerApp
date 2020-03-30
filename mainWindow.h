#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include "myModel.h"

class mainWindow : public QMainWindow
{
	Q_OBJECT
private:
	myModel* model;
	Programmer pr;
	Repository* repo;


public:
	mainWindow(Repository* repo,myModel* model,Programmer pr, QWidget*parent = Q_NULLPTR);

private:
	Ui::mainWindowClass ui;
	int workingOn;
private slots:

	void addTask();

	void deleteTask();

	void solveTask();

	void TaskSolved();
};
