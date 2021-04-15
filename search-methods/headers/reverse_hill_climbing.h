#pragma once

#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include<unordered_map>
#include "windows.h"
#include "psapi.h"
#include<stdio.h>
#include<string>
#include"../../criticality/header/ck_search.h"
#include"../../criticality/header/systemState.h"

class reverse_hill_climbing : public ck_search {

public:

	/*inline reverse_hill_climbing(systemState Problem);*/

	reverse_hill_climbing();

	reverse_hill_climbing(const char*);

	~reverse_hill_climbing();

	std::vector<unsigned int> get_result();

	/*inline systemState get_result();*/

private:

	//systemState problem;

	//systemState result;

	inline systemState highest_value(systemState current);

	void main();

	criticality initial_data;
	ck_search mu_file;
	unsigned int TYPE_SEARCH;
	unsigned int no_of_visited_solutions = 0;
	const char* CK_PARAM_FILE;
	std::unordered_map<unsigned int, std::vector<std::vector<unsigned int>>> ckList;
	std::stack<std::vector<unsigned int>> lopt;
	std::string param_str;
	systemState bestResult;
	clock_t elapsed_time;
	unsigned int ktuplefound = 0;


	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
private:
	void report();
	bool evalue_new_tuple(systemState);
	void save_result(std::vector<unsigned int>);
	void convert_result();
	systemState create_population();
};