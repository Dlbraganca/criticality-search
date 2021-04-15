#include"../../criticality/header/ck_search.h"
#include"../../criticality/header/systemState.h"
#include<vector>
#include <algorithm>
#include"windows.h"
#include"psapi.h"
#include<unordered_map>


class a_search : public ck_search {

protected:
	std::unordered_map<std::string, int> visited_states;
	ck_search mu_file;
	unsigned int TYPE_SEARCH;
	unsigned int no_of_visited_solutions = 0;
	const char* CK_PARAM_FILE;
	std::stack<std::vector<unsigned int>> lopt;
	std::string param_str;
public:
	a_search();
	~a_search() {};
	a_search(const char*, std::string);
	//methods
	a_search(unsigned int KLIM, unsigned int KMIN, unsigned int KMAX, unsigned int DIM, std::string CRIT_TYPE, criticality&);
	a_search(const char*, criticality&);
	void agent_measurement();
	void agent_munit();
	//void save_state();
private:
	void printavetor(std::vector<unsigned int>);
	void free_memory(std::vector<unsigned int>);
	void report();
	unsigned test_ck_4(std::vector<unsigned int>);
	unsigned int test_ck_munit(std::vector<unsigned int>);

};