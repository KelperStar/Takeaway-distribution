#include "rider.h"

#include<cmath>

void rider::print() {
	printf("rider%d:", id);
	for (std::vector<int>::iterator it = route.begin(); it != route.end(); it++) {
		printf("%d ", *it);
	}
	putchar('\n');
}

void rider::clear() {
	route.clear();
	route.push_back(0);
	spendTime.clear();
	id = 0;
	toBeATaskNum = 0;
	breakTaskNum = 0;
	finishTaskNum = 0;
	failTaskNum = 0;
	toDoNum = 1;
}

void rider::judgeBreak(const problem &input) {
	if (route.size() <= 2) {
		for (int i = 0;i <= input.getTaskNum();i++) {
			spendTimeIndex.push_back(0);
		}
		int newX = abs(input.allTask[route.back() - 1].x - 8);
		int newY = abs(input.allTask[route.back() - 1].y - 8);
		int distance = newX + newY;
		spendTime.push_back(distance + birthTime);
		return;
	}
	else{
		int newX = abs(input.allTask[route.back() - 1].x - input.allTask[route[route.size() - 2]- 1].x);
		int newY = abs(input.allTask[route.back()- 1].y - input.allTask[route[route.size() - 2]- 1].y);
		int distance = newX + newY + spendTime.back();
		if (distance < input.allTask[route.back() - 1].start) {
			distance = input.allTask[route.back() - 1].start;
		}
		spendTimeIndex[route[route.size() - 2]] = toDoNum;
		toDoNum = toDoNum + 1;
		spendTime.push_back(distance);
	}
	if (!(route.back() & 1)) {
		int aTaskTime = spendTime.back() - input.allTask[route.back() - 1].start;
		if (aTaskTime <= 30) {
			finishTaskNum = finishTaskNum + 1;
		}
		else if (aTaskTime > 30 && aTaskTime <= 60) {
			breakTaskNum = breakTaskNum + 1;
		}
		else {
			failTaskNum = failTaskNum + 1;
		}
	}
}

void rider::getBirthTime(const problem &input) {
	if (route.size() <= 1) {
		birthTime = 0;
		return;
	}
	birthTime = input.allTask[route[1] - 1].start;
	for (int i = 2;i < route.size(); i++) {
		if (input.allTask[route[i] - 1].start < birthTime) {
			birthTime = input.allTask[route[i] - 1].start;
		}
	}
}