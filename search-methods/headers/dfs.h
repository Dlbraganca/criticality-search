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

class dfs : public ck_search
{
public:
	dfs(const char* CK_PARAM_FILE);
	dfs(systemState, criticality&, std::string);
private:
	int no_of_visited_solutions;
	void main();
	void report();
	std::string get_hash(std::vector<unsigned int> vector) {
		std::string hashKey;
		for (size_t i = 0; i < vector.size(); i++)
		{
			hashKey.push_back(vector[i]);
		}
		return hashKey;
	}
	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
};


