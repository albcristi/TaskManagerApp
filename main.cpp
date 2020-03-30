#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository* repo = new Repository();
	repo->loadTasks();
	repo->loadProgrammers();
	repo->sortData();
	myModel* model = new myModel(repo);
	std::vector<mainWindow*> windows;
	for (auto prog : repo->getProgrammers()) {
		windows.push_back(new mainWindow(repo, model, prog));
	}
	for (auto window : windows) {
		window->show();
	}
	return a.exec();
}
