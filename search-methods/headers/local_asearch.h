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

class local_asearch : public ck_search
{
public:
	local_asearch(const char* CK_PARAM_FILE);
	local_asearch(systemState, criticality& , std::string);

	std::stack<std::vector<unsigned int>> get_result() { return result; }
private:

	std::stack<std::vector<unsigned int>> result;
	systemState system;
	criticality critical_data;
	std::string ck_param_file;

	void main();
	std::string get_hash(std::vector<unsigned int> vector) {
		std::string hashKey;
		for (size_t i = 0; i < vector.size(); i++)
		{
			hashKey.push_back(vector[i]);
		}
		return hashKey;
	}
};


