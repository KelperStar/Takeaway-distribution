#ifndef SOLUTION_H
#define SOLUTION_H

#include<cstdio>
#include<list>
#include<vector>

#include "task.h"
#include"problem.h"
#include "rider.h"

class solution {
public:
	void print();
	void generate(const problem &input);
	int fitness(const problem &input);
	void decode(const problem &input);
	static int cmp(solution &solA, solution &solB, const problem &input);
	bool lessTime(std::pair<int, int> a, std::pair<int, int> b);
	std::vector<int> allPaths;
	std::vector<rider> allRiders;
	std::vector<int> workingRiders;
	bool feasible;
};
#endif
