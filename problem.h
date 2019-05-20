#ifndef PROBLEM_H
#define PROBLEM_H

#include<vector>
#include"task.h"

class problem {
public:
	bool load(const char* filename);
	std::vector<task> allTask;
	int getDistance(int fromLocation, int toLocation);
	void print();
	int getTaskNum() const;
};
#endif
