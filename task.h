#ifndef TASK_H
#define TASK_H

class task {
public:
	task(int id, int x, int y, int start, int mid, int end);
	int id;
	int start, mid, end;
	int x, y;
};
#endif
