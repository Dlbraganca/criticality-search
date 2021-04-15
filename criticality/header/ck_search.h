#pragma once

//#ifdef USE_FAST_CRITICALITY_H
#include "./criticality.h"// !FAST_CRITICALITY_H
//#else
//#include "criticality.h"// !CRITICALITY_H
//#endif

#ifndef CK_SEARCH_H
#define CK_SEARCH_H
#endif

#include <time.h>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>




class ck_search{
protected:
	// members
	unsigned int kmin,kmax,klim,dim;
	std::string crit_type,search_method;
	time_t tbegin, tend;
	double elapsed_time;
	std::vector<unsigned int> T;
	std::stack<std::vector<unsigned int>> lopt, lopt_buff;
	criticality critical_data;
public:	
	// methods
	ck_search();
	ck_search(unsigned int, unsigned int, unsigned int, unsigned int, std::string, criticality&);
	ck_search(const char*, criticality&);
	ck_search(const char*);
	~ck_search();
	void read_problem_parameters(const char*);
	unsigned int get_klim() { return klim; };
	unsigned int get_kmin() { return kmin; };
	unsigned int get_kmax() { return kmax; };
	unsigned int get_dim() { return dim; };
	std::string get_crit_type() { return crit_type; };
	std::string get_search_method() { return search_method; };
	std::stack<std::vector<unsigned int>>get_lopt() { return lopt_buff; };
	void set_klim(const unsigned int &KLIM) { klim=KLIM; };
	void set_kmin(const unsigned int &KMIN) { kmin=KMIN; };
	void set_kmax(const unsigned int &KMAX) { kmax=KMAX; };
	void set_dim(const unsigned int &DIM) { dim=DIM; };
	void set_crit_type(std::string CRIT_TYPE) { crit_type=CRIT_TYPE; };
	void set_search_method(std::string SEARCH_METHOD) { search_method= SEARCH_METHOD; };
	criticality get_critical_data() { return critical_data; };
	
	virtual void save_state() {/*not implemented*/ };
	virtual void load_state() {/*not implemented*/ };
	virtual void report() {/*not implemented*/ };
	virtual void search() {/*not implemented*/ };

	//void save_state() {/*not implemented*/ };
	//void load_state() {/*not implemented*/ };
	//void report() {/*not implemented*/ };
	//void search() {/*not implemented*/ };

	std::stack<std::vector<unsigned int>> get_lopt_buffer() { return lopt_buff; }
};
/*
class bb_ck : public ck_search{
public:
	// members
	unsigned int no_of_visited_solutions;
	std::vector<unsigned int> Tk;
	//double (*f)(std::vector<unsigned int>);
	double l_inf,l_sup;
	// methods
	bb_ck();
	bb_ck(unsigned int KLIM, unsigned int KMIN, unsigned int KMAX, unsigned int DIM, std::string CRIT_TYPE, double (*BOUND_FUNC)(std::vector<unsigned int>));// : ck_search( KLIM,  KMIN,  KMAX,  CRIT_TYPE); (NO .CPP)
	virtual void branch(); // ramifica subproblema
	void bound(); // determina limite inferior do subproblema
	virtual void process_node(); // processa atual subconjunto
	virtual void search(); //double (*l_inf)(std::vector<unsigned int> T) -> limite inferior da solucao
	virtual void report(); // imprime resultados finais da busca
	friend double eval_criticality(criticality Ck, std::vector<unsigned int> x);
	
};

class dfs_ck : public bb_ck{
public:
	//members
	std::stack<std::vector<unsigned int>> Asp;
	//methods
	dfs_ck();
	dfs_ck(unsigned int KLIM, unsigned int KMIN, unsigned int KMAX, unsigned int DIM, std::string CRIT_TYPE, double (*BOUND_FUNC)(std::vector<unsigned int>));// : bb_ck( KLIM,  KMIN,  KMAX,  CRIT_TYPE); (NO .CPP)
	void branch();
	//void process_node();
	void save_state();
	void load_state();
	void search();
	void report();
};

class bfs_ck : public bb_ck{
public:
	//members
	std::queue<std::vector<unsigned int>> Asp;
	//methods
	bfs_ck();
	bfs_ck(unsigned int KLIM, unsigned int KMIN, unsigned int KMAX, unsigned int DIM, std::string CRIT_TYPE, double (*BOUND_FUNC)(std::vector<unsigned int>));// : bb_ck( KLIM,  KMIN,  KMAX,  CRIT_TYPE); (NO .CPP)
	void branch();
	//void process_node();
	void save_state();
	void load_state();
	void search();
	void report();
};
*/