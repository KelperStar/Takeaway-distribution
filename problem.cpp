#include "problem.h"

bool problem::load(const char* filename) {
	FILE *fp = fopen(filename, "r");

	if (fp == NULL)
		return false;

	int tmpId;
	int id = 1;
	while ((fscanf(fp, "%d", &tmpId) != EOF)) {
		int x0, y0, x1, y1;
		int start;
		fscanf(fp, "%d%d%d%d%d", &start, &x0, &y0, &x1, &y1);
		task newTask0(id, start, start + 30, start + 60, x0, y0);
		allTask.push_back(newTask0);
		id = id + 1;
		task newTask1(id, start, start + 30, start + 60, x1, y1);
		allTask.push_back(newTask1);
		id = id + 1;
	}
	fclose(fp);
	return true;
}

void problem::print() {
	size_t len = allTask.size();
	for (size_t i = 0;i < len;i++) {
		printf("%d %d %d %d %d %d\n", allTask[i].id, allTask[i].start, allTask[i].mid, allTask[i].end, allTask[i].x, allTask[i].y);
	}
	return;
}

int problem::getTaskNum() const {
	return allTask.size();
}

int problem::getDistance(int fromLocation, int toLocation) {
	int newX = abs(allTask[fromLocation].x - allTask[toLocation].x);
	int newY = abs(allTask[fromLocation].y - allTask[toLocation].y);
	return newX + newY;
}