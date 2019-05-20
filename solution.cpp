#include<algorithm>

#include"solution.h"

using namespace std;

void solution::print() {
	printf("The whole riders are %d,%s\n", allRiders.size(), (feasible) ? "feasible" : "infeasible");
	printf("The solution code is:");
	for (vector<int>::const_iterator it = allPaths.begin(); it != allPaths.end(); it++) {
		printf("%d ",*it);
	}
	putchar('\n');
	for (int i = 0;i < allRiders.size();i++) {
		allRiders[i].print();
	}
	return;
}

void solution::generate(const problem &input) {
	vector<int> ids(input.getTaskNum());
	for (int i = 0;i < ids.size();i++) {
		ids[i] = i + 1;
	}
	random_shuffle(ids.begin(), ids.end());
	vector<bool> judgeIds(input.getTaskNum());
	for (int i = 0;i < judgeIds.size();i++) {
		judgeIds[i] = false;
	}
	while (!ids.empty()) {
		int tmpId = ids.front();
		if (!(tmpId & 1)) {
			if (judgeIds[tmpId - 2]) {
				allPaths.push_back(tmpId);
				judgeIds[tmpId - 1] = true;
				ids.erase(ids.begin(),ids.begin() + 1);
			}
			else {
				ids.push_back(tmpId);
				ids.erase(ids.begin(), ids.begin() + 1);
			}
		}
		else {
			allPaths.push_back(tmpId);
			judgeIds[tmpId - 1] = true;
			ids.erase(ids.begin(), ids.begin() + 1);
		}
	}
}

void solution::decode(const problem &input) {
	bool addARider = true;
	int tmpId = 1;
	rider newRider;
	vector<int> judgeIds(allPaths.size());
	for (vector<int>::const_iterator it = allPaths.begin(); it != allPaths.end(); it++) {
		if (newRider.toBeATaskNum > 12) {
			allRiders.push_back(newRider);
			addARider = true;
		}
		if (addARider) {
			newRider.clear();
			newRider.id = tmpId;
			if (tmpId == 1) {
				newRider.birthTime = input.allTask[0].start;
			}
			else {
				newRider.birthTime = allRiders.back().spendTime.back();
			}
			tmpId = tmpId + 1;
			addARider = false;
		}
		if (judgeIds[*it - 1] == 0) {
			newRider.route.push_back(*it);
			newRider.toBeATaskNum = newRider.toBeATaskNum + 1;
			if (*it & 1) {
				judgeIds[*it] = newRider.id;
			}
			newRider.judgeBreak(input);
		}
		else if(judgeIds[*it - 1] == newRider.id){
			newRider.route.push_back(*it);
			newRider.toBeATaskNum = newRider.toBeATaskNum - 1;
			newRider.judgeBreak(input);
		}
		else {
			allRiders[judgeIds[*it - 1] - 1].route.push_back(*it);
			allRiders[judgeIds[*it - 1] - 1].toBeATaskNum = allRiders[judgeIds[*it - 1] - 1].toBeATaskNum - 1;
			allRiders[judgeIds[*it - 1] - 1].judgeBreak(input);
		}
	}
	if (!newRider.route.empty()) {
		allRiders.push_back(newRider);
	}
}

int solution::fitness(const problem &input) {
	/*vector<pair<int,int>> departTimeTable;
	for (int i = 0;i < allRiders.size(); i++) {
		departTimeTable.push_back(make_pair(i, allRiders[i].birthTime));
	}
	sort(departTimeTable.begin(), departTimeTable.end(), lessTime);
	int money = 1000;
	int time = 0;
	int finishRiderNum = 0;
	while (finishRiderNum != allRiders.size()) {
		while (time == departTimeTable.front().second) {
			workingRiders.push_back(departTimeTable.front().first);
			departTimeTable.erase(departTimeTable.begin());
		}

	}*/
	int rank = 0;
	for (int i = 0; i < allRiders.size(); i++) {
		allRiders[i].getBirthTime(input);
		rank = rank + (50 * allRiders[i].finishTaskNum + 20 * allRiders[i].breakTaskNum - allRiders.size() * 10) / (allRiders[i].failTaskNum + 1);
	}
	if (rank <= 0) {
		rank = 1;
	}
	return rank;
}

    int solution::cmp(solution &solA,solution &solB, const problem &input) {
	    if (solA.fitness(input) > solB.fitness(input) ){
		    return 1;
	    }
	    else {
		    return -1;
	    }
}

bool solution::lessTime(std::pair<int, int> a, std::pair<int, int> b) {
	return  a.second < b.second;
}