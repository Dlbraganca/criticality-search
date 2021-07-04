#pragma once
#include<vector>
#include<string>
#include"criticality.h"

class systemState {

protected:
	std::vector<unsigned int> CKLIST;
	double PATHCOST;
	double DEEPTH;
	double HEURISTIC;
	double F;
	criticality CRITICAL_DATA;
	std::string TYPE_SEARCH;

public:
	systemState();
	~systemState();
	systemState(std::vector<unsigned int>, criticality&, std::string);
	systemState(std::vector<unsigned int>, criticality&, std::string, systemState);
	std::vector<unsigned int> get_cklist() { return CKLIST; };
	double get_heuristic() { return HEURISTIC; };
	double get_f() { return F; }
	void set_heuristic(double value) { HEURISTIC = value; }
	void set_f(double value) { F = value; };
	unsigned int get_deepth() { return DEEPTH; };
	bool measurement_evalueCK();
	bool munit_evalueCK();
	bool evalueCK();
	bool evalueCK(std::string);
	double get_path_cost() { return PATHCOST; }
private:
	unsigned int set_depth();
	double measurement_heuristic();
	double munit_heuristic();
};