#pragma once
#include<vector>
#include<string>
#include"criticality.h"

class systemState {

protected:
	std::vector<unsigned int> CKLIST;
	double DEEPTH;
	double HEURISTIC = 0;
	criticality CRITICAL_DATA;
	std::string TYPE_SEARCH;

public:
	systemState();
	~systemState();
	systemState(std::vector<unsigned int>, criticality&, std::string);
	std::vector<unsigned int> get_cklist() { return CKLIST; };
	double get_heuristic() { return HEURISTIC; };
	void set_heuristic(double value) { HEURISTIC = value; }
	unsigned int get_deepth() { return DEEPTH; };
	bool measurement_evalueCK();
	bool munit_evalueCK();
	bool evalueCK();
private:
	unsigned int set_depth();
	double measurement_heuristic();
	double munit_heuristic();
};