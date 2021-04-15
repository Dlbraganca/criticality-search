#pragma once
#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include<vector>
#include<chrono>
#include<random>
#include "windows.h"
#include "psapi.h"
#include"../../criticality/header/ck_search.h"
#include"../../criticality/header/systemState.h"

class SimulatedAnnealing : public ck_search
{
public:

	SimulatedAnnealing(const char*);
	SimulatedAnnealing();
	~SimulatedAnnealing();

	systemState get_result();

private:

	systemState problem;
	systemState result;
	unsigned int no_of_visited_solutions = 0;
	double tempeture = 100;
	double decay = 0.1;
	std::stack<std::vector<unsigned int>> lopt;

	systemState RandomValue(systemState current);

	bool RandomProbability(double delE, double T);

	void main(systemState);

	void report();

	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
};
#endif