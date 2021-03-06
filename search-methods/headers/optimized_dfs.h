#pragma once
#pragma once
#include"../../criticality/header/ck_search.h"
#include"../../criticality/header/systemState.h"
#include"./local_asearch.h"
#include<vector>
#include <algorithm>
#include"windows.h"
#include"psapi.h"
#include<unordered_map>
#include<chrono>
#include<random>

class Optimized_DFS : public ck_search
{
public:
	Optimized_DFS(const char*);
	void report();
private:
	unsigned int populationSize = 5;
	std::unordered_map<std::string, std::vector<unsigned int>> ckList;
	unsigned int no_of_visited_solutions = 0;


	void main();

	double perfomanceTest = 100.0;

	void result_evaluation(std::vector<unsigned int>);
	systemState create_population();
	std::string get_hash(std::vector<unsigned int> vector) {
		std::string hashKey;
		for (size_t i = 0; i < vector.size(); i++)
		{
			hashKey.push_back(vector[i]);
		}
		return hashKey;
	}
	systemState hill_climbing(systemState);
	void convertResult();
	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
};
