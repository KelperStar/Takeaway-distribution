#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<vector>
#include <list>
#include <algorithm>
#include "problem.h"
#include "solution.h"
#include "evolution.h"

using namespace std;

int main(int argc, char *argv[]) {
	clock_t start = clock();
	unsigned int seed;
	if (argc > 2) {
		seed = (unsigned int)atoi(argv[2]);
	}
	else {
		seed = (unsigned int)time(NULL);
	}//设置随机种子数
	printf("Seed = %d\n", seed);
	srand(seed);

	//读入数据
	problem input;
	if (!input.load("C://Users//Abigail//source//repos//Project1//Debug//sales1.txt")) {
		puts("Unable to open input file!");
		return 1;
	}
	else {
		input.print();
	}
	getchar();
	
	//初始化种群
	vector<solution> population(100);
	for (vector<solution>::iterator it = population.begin();it != population.end(); ++it) {
		it->generate(input);//随机生成种群
		it->decode(input);
		it->print();
	}
	getchar();
	
	//进化迭代
	for(int run = 0; run < 500; run++){
		putchar('*');

		vector<solution> evoluting(population.begin(), population.end());
		for (int off = 0;off < 50; off++) {
			solution parent1 = tournament(population, input);
			solution parent2 = tournament(population, input);

			solution off1 = crossover(parent1, parent2, input);
			solution off2 = crossover(parent1, parent2, input);
			evoluting.push_back(off1);
			evoluting.push_back(off2);
		}
		population.clear();
		environmental(evoluting, population, input);
	}
	putchar('\n');

	// 输出结果
	pair<int, int> bestSolution(0, population[0].fitness(input));
	for (int i = 0; i < population.size(); i++) {
		int thisFitness = population[i].fitness(input);
		if (thisFitness > bestSolution.second) {
			bestSolution = make_pair(i, thisFitness);;
		}
	}
	population[bestSolution.first].print();
	getchar();
	clock_t end = clock();

	printf("%.3f second\n", ((double)(end)-start) / CLOCKS_PER_SEC);
	return 0;
}