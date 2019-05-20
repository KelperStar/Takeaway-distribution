#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "problem.h"
#include "solution.h"

using namespace std;

vector<int> getSegment(const solution &pb);
solution crossover(const solution &fatherSolution, const solution &motherSolution, const problem &input);
void mutation(solution offSolution, const problem &input);
const solution &tournament(vector<solution> &population, const problem &input);
void environmental(vector<solution> &group, vector<solution> &newgroup, const problem &input);

#endif
