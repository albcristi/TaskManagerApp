#include "Repository.h"

#include <fstream>
#include <sstream>

Repository::Repository()
{
}

void Repository::loadTasks()
{
	std::ifstream content("tasks.txt");
	Task tsk{};
	std::vector<std::string> fragm;
	std::string line;
	while (content >> line) {
		fragm = this->fragmentate(line, ',');
		if (fragm.size() == 3) {
			tsk.setDescription(fragm[0]);
			tsk.setStatus(fragm[1]);
			tsk.setId(std::stoi(fragm[2]));
			this->tasks.push_back(tsk);
		}
	}
	content.close();
}

void Repository::loadProgrammers()
{
	std::ifstream content("programmers.txt");
	Programmer pr{};
	std::vector<std::string> fragm;
	std::string line;


	while (content >> line) {
		fragm = this->fragmentate(line, ',');
		if (fragm.size() == 2) {
			pr.setName(fragm[0]);
			pr.setId(std::stoi(fragm[1]));
			this->programmers.push_back(pr);
		}
	}

	content.close();
}


std::vector<std::string> Repository::fragmentate(std::string str, char delimit)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimit)) {
		result.push_back(token);
	}

	return result;
}

void Repository::sortData()
{


	std::sort(this->tasks.begin(), this->tasks.end(), [](Task & t1, Task & t2) {return t1.getStatus() < t2.getStatus(); });


}

void Repository::saveData()
{
	std::ofstream file("tasks.txt", std::ios::out);
	file.close();
	std::ofstream newFile("tasks.txt", std::ios::app);

	for (auto task : this->tasks) {
		std::string s;
		s.append(task.getDescription() + ',' + task.getStatus() + ',');
		std::stringstream ss;
		ss << task.getId();
		s.append(ss.str()+'\n');
		newFile << s;
	}
	newFile.close();
}

Repository::~Repository()
{
}
