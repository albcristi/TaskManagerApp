#pragma once
#include <string>

class Programmer
{
	std::string name;
	int id;
public:
	Programmer();
	Programmer(std::string _name, int _id) { this->name = _name; this->id = _id; }
	Programmer(const Programmer& co) { this->name = co.name; this->id = co.id; }
	Programmer& setName(std::string _name) { this->name = _name; return *this; }
	Programmer& setId(int _id) { this->id = _id; return *this; }
	std::string getName() { return this->name; }
	int getId() { return this->id; }
	~Programmer();
};

