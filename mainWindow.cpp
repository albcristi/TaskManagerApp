#include "mainWindow.h"
#include <qerrormessage.h>

mainWindow::mainWindow(Repository* repo, myModel* model, Programmer pr, QWidget *parent)
	: QMainWindow(parent),repo(repo),model(model),pr(pr)
{
	ui.setupUi(this);
	setWindowTitle(pr.getName().c_str());
	this->ui.doneButton->setDisabled(true);
	QFont f{ "Times",15 };
	this->ui.descriptionBuddy->setFont(f);
	this->ui.descriptionLabel->setFont(f);
	this->ui.tasksTable->setModel(model);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &mainWindow::deleteTask);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &mainWindow::addTask);
	QObject::connect(this->ui.startButton, &QPushButton::clicked, this, &mainWindow::solveTask);
	QObject::connect(this->ui.doneButton, &QPushButton::clicked, this, &mainWindow::TaskSolved);
}

void mainWindow::addTask() {
	std::string description = this->ui.descriptionBuddy->text().toStdString();
	if (description == "") {
		QErrorMessage* msg = new QErrorMessage();
		msg->showMessage("NO DESCRIPTION HAS BEEN PROVIDED\n");
		return;
	}
	this->ui.descriptionBuddy->clear();
	Task tsk{};
	tsk.setId(-1);
	tsk.setStatus("open");
	tsk.setDescription(description);
	this->repo->add(tsk);
	this->repo->sortData();
	this->model->signalRowAdded();
	this->repo->saveData();
}
void mainWindow::deleteTask()
{
	std::string description = this->ui.descriptionBuddy->text().toStdString();
	if (description == "") {
		QErrorMessage* msg = new QErrorMessage();
		msg->showMessage("NO DESCRIPTION HAS BEEN PROVIDED\n");
		return;
	}
	Task tsk{};
	tsk.setDescription(description);
	int oldsize = this->repo->getSize();
	int pos = this->repo->remove(tsk);
	if (oldsize == this->repo->getSize()) {
		QErrorMessage* msg = new QErrorMessage();
		msg->showMessage("Task not found!");
		return;
	}
	this->repo->sortData();


	this->model->removeRow(pos);
	this->repo->sortData();
	this->repo->saveData();
}

void mainWindow::solveTask()
{
	QModelIndex index = this->ui.tasksTable->currentIndex();
	if (index.row() < 0) {
		QErrorMessage* msg = new QErrorMessage();
		msg->showMessage("No selected task!\n");
		return;
	}
	Task  tsk = this->repo->getTasks()[index.row()];
	if (tsk.getStatus() != "open") {
		QErrorMessage* msg = new QErrorMessage();
		msg->showMessage("You can not solve this task!\n");
		return;
	}
	this->workingOn = index.row();
	tsk.setStatus("progress");
	tsk.setId(this->pr.getId());
	this->repo->update(tsk);
	this->repo->sortData();
	this->model->signalRowChanged();
	this->ui.startButton->setDisabled(true);
	this->ui.doneButton->setDisabled(false);
	this->repo->saveData();
}

void mainWindow::TaskSolved()
{
	this->ui.doneButton->setDisabled(true);
	this->ui.startButton->setDisabled(false);
	Task ts = this->repo->getTasks()[this->workingOn];
	ts.setStatus("closed");
	ts.setId(this->pr.getId());
	this->repo->update(ts);
	this->repo->sortData();
	this->model->signalRowChanged();
	this->repo->saveData();
}


