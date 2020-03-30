#pragma once
#include "Task.h"
#include "Programmer.h"
#include <vector>
#include <algorithm>

class Repository
{
private:
	std::vector<Task> tasks;
	std::vector<Programmer> programmers;
public:
	Repository();
	void loadTasks();
	void loadProgrammers();

	std::vector<std::string> fragmentate(std::string str, char delimit);
	std::vector<Task> getTasks() { return this->tasks; }

	int getSize() { return this->tasks.size(); }

	std::vector<Programmer> getProgrammers() { return this->programmers; }
	void add(Task ts) {
		this->tasks.push_back(ts);
	}

	int remove(Task ts) {
		int pos = -1;
		if (find(this->tasks.begin(), this->tasks.end(), ts) == this->tasks.end()) {
			return -1;
		}
		pos = find(this->tasks.begin(), this->tasks.end(), ts) - this->tasks.begin();
		this->tasks.erase(std::find(this->tasks.begin(), this->tasks.end(), ts));
		return pos;
	}
	void sortData();

	void update(Task tsk) {
		for (int i = 0; i < this->tasks.size(); i++) {
			if (this->tasks[i] == tsk) {
				this->tasks[i] = tsk;
			}
		}
	}

	void saveData();
	~Repository();
};

