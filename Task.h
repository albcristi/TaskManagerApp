#pragma once
#include <string>
class Task
{
private:
	std::string description;
	std::string status;
	int id_prog;
public:
	Task();
	Task(std::string _description, std::string _status, int _id_prog) { this->description = _description; this->status = _status; this->id_prog = _id_prog; }
	Task(const Task& co) {
		this->description = co.description;
		this->id_prog = co.id_prog;
		this->status = co.status;
	}

	Task& setDescription(std::string _description) { this->description = _description; return *this; }
	Task& setStatus(std::string _status) { this->status = _status; return *this; }
	Task& setId(int _id) { this->id_prog = _id; return *this; }
	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	int getId() { return this->id_prog; }

	bool operator==(const Task& t) { return this->description == t.description; }
	~Task();
};

