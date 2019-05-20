#include<vector>
#include<algorithm>
#include "evolution.h"

using namespace std;

vector<int> getSegment(const solution &pb){
	vector<int> newGeneSegment;
	vector<int> geneSegment;
	newGeneSegment.clear();
	bool flag = false;
	int getStart = rand() % (pb.allPaths.size() - 1);
	if (!(getStart & 1)) {
		getStart = getStart + 1;
	}
	int group = 0;
	int maxGroup = rand() % (pb.allPaths.size() / 2);
	if (maxGroup == 0) {
		maxGroup = 1;
	}
	for (int i = 0;i < pb.allPaths.size();i++) {
		if (getStart == pb.allPaths[i]) {
			flag = true;
		}
		if (flag == true) {
			newGeneSegment.push_back(pb.allPaths[i]);
		}
	}
	for (int i = 0; i < newGeneSegment.size(); i++) {
		if (!(newGeneSegment[i] & 1)) {
			vector<int>::iterator result = find(newGeneSegment.begin(), newGeneSegment.end(), newGeneSegment[i] - 1);
			if (result == newGeneSegment.end()) {
				newGeneSegment[i] = 0;
			}
		}
	}
	geneSegment.clear();
	for (int i = 0;i < newGeneSegment.size();i++) {
		if (group <= maxGroup && newGeneSegment[i] != 0) {
			geneSegment.push_back(newGeneSegment[i]);
				if (!(newGeneSegment[i] & 1)) {
					group = group + 1;
				}
		}
	}
	if (geneSegment.empty()) {
		geneSegment.push_back(1);
		geneSegment.push_back(2);
	}
	return geneSegment;
}

solution crossover(const solution &pa, const solution &pb, const problem &input) {
	solution offspring = pa;
	vector<pair<int, int>> potentialZero;
	vector<int> geneSegment = getSegment(pb);
	for (int i = 0; i < offspring.allPaths.size(); i++) {
		vector<int>::iterator it = find(geneSegment.begin(), geneSegment.end(), offspring.allPaths[i]);
		if (it != geneSegment.end()) {
			offspring.allPaths[i] = 0;
		}
	}
	for (int i = 0; i < offspring.allPaths.size(); i++) {
		if (offspring.allPaths[i] != 0) {
			int tmp = offspring.allPaths[i];
			int distance = abs(input.allTask[tmp - 1].x - input.allTask[geneSegment[0] - 1].x) + abs(input.allTask[tmp - 1].y - input.allTask[geneSegment[0] - 1].y);
			pair<int, int> value(i, distance);
			potentialZero.push_back(value);
		}
	}
	if (potentialZero.size() == 0) {
		return offspring;
	}
	pair <int, int> findMinPair = potentialZero[0];
	for (int i = 0; i < potentialZero.size(); i++) {
		if (potentialZero[i].second < findMinPair.second) {
			findMinPair = potentialZero[i];
		}
	}
	int insertIndex = findMinPair.first;
	bool findIt = false;
	while (!findIt && insertIndex >= 0) {
		if (offspring.allPaths[insertIndex] == 0) {
			findIt = true;
		}
		if (!findIt) {
			insertIndex = insertIndex - 1;
		}
	}
	insertIndex = findMinPair.first;
	while (!findIt && insertIndex < offspring.allPaths.size()) {
		if (offspring.allPaths[insertIndex] == 0) {
			findIt = true;
		}
		if (!findIt) {
			insertIndex = insertIndex + 1;
		}
	}
	int j = 0;
	for (int i = insertIndex; i < offspring.allPaths.size(); i++) {
		if (offspring.allPaths[i] == 0) {
			offspring.allPaths[i] = geneSegment[j];
			j = j + 1;
		}
	}
	for (int i = 0; i < insertIndex; i++) {
		if (offspring.allPaths[i] == 0) {
			offspring.allPaths[i] = geneSegment[j];
			j = j + 1;
		}
	}
	return offspring;
}

void mutation(solution offSolution, const problem &input) {
	if (rand() / offSolution.allPaths.size() < 2) {
		int randomMove1, randomMove2;
		randomMove1 = rand() % offSolution.allPaths.size();
		vector<int>::iterator theChosen1 = offSolution.allPaths.begin();
		advance(theChosen1, randomMove1);
		vector<int>::iterator theChosen2 = offSolution.allPaths.begin();
		randomMove2 = rand() % offSolution.allPaths.size();
		advance(theChosen2, randomMove2);
		if (*theChosen2 & 1) {
			swap(theChosen1, theChosen2);
		}
		else {
			for (int i = 0; i < offSolution.allPaths.size(); i++) {
				if (offSolution.allPaths[i] == *theChosen2 - 1) {
					if (randomMove1 > i) {
						swap(theChosen1, theChosen2);
					}
				}
			}
		}
	}
}

const solution& tournament(std::vector<solution> &population, const problem &input) {
	int randomMove1, randomMove2;
	randomMove1 = rand() % population.size();
	randomMove2 = rand() % population.size();
	int result = solution::cmp(population[randomMove1], population[randomMove2], input);
	if (result == 0) {
		result = (rand() % 2) * 2 - 1;   // -1 or 1
	}
	if (result > 0) {
		return population[randomMove1];
	}
	else {
		return population[randomMove2];
	}
}

void environmental(vector<solution> &group, vector<solution> &newgroup, const problem &input) {
	vector<int> ranking;
	ranking.push_back(0);
	int nowSolutionNum = 0;
	int maxSolutionNum = 100;
	for (int i = 0;i < group.size(); i++) {
		ranking.push_back(ranking.back() + group[i].fitness(input));
	}
	while (nowSolutionNum < maxSolutionNum) {
		int key = rand() % ranking.back();
		int i = 0;
		while (key >= ranking[i] && i < group.size()) {
			i = i + 1;
		}
	newgroup.push_back(group[i - 1]);
	nowSolutionNum = nowSolutionNum + 1;
	}
}