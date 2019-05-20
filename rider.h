#ifndef RIDER_H
#define RIDER_H

#include<vector>

#include "problem.h"

class rider {
public:
	void print();
	void clear();
	void judgeBreak(const problem &input);
	void getBirthTime(const problem &input);
	int id, toBeATaskNum, breakTaskNum, finishTaskNum, failTaskNum, toDoNum, birthTime;
	std::vector<int> route;
	std::vector<int> spendTimeIndex;
	std::vector<int> spendTime;
};
#endif