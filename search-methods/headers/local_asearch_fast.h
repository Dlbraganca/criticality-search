#pragma once
#include<vector>
#include<chrono>
#include "windows.h"
#include "psapi.h"
#include<stdio.h>
#include<string>
#include<stack>
#include<unordered_map>
#include"../../criticality/header/ck_search.h"
#include"../../criticality/header/systemState.h"

class local_asearch_fast : public ck_search
{
public:
	local_asearch_fast(const char* CK_PARAM_FILE);
	local_asearch_fast(systemState, criticality&, std::string);

	std::stack<std::vector<unsigned int>> get_result() { return result; }
private:
	double stoppingCriterion = 0.03;
	double metric = 100;
	std::stack<std::vector<unsigned int>> result;
	systemState system;
	criticality critical_data;
	std::string ck_param_file;
	unsigned int no_of_visited_solutions = 0;
	clock_t elapsed_time;
	std::vector<systemState> pile;
	std::vector<systemState> temporaryPile;
	std::vector<unsigned int> freePosition;
	systemState get_best_heuristic(std::vector<systemState>&);
	void main();
	std::string get_hash(std::vector<unsigned int> vector) {
		std::string hashKey;
		for (size_t i = 0; i < vector.size(); i++)
		{
			hashKey.push_back(vector[i]);
		}
		return hashKey;
	}
	systemState fast_sort();
	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
};


