#pragma once
#pragma once
#ifndef CRITICALITY_H
#define CRITICALITY_H
#endif
#include <armadillo>
#include <vector>
#include <stack>
#include <algorithm>

class criticality {
protected:
	std::stack<std::vector<unsigned int>> meas_ck, branch_ck, mu_ck;
	arma::mat H, M, A, G, E, U;
	/* H: matriz jacobiano
	G: matriz de ganho
	A: matriz de incidencia ramo-no
	M: matriz incidencia medida-ramo
	E: matriz de covariancia dos residuos
	*/
	std::size_t nm, ns, mu_size;
	std::vector<std::size_t> mu_location, meas_location;
public:
	//double det;
	~criticality();
	criticality();
	criticality(const char*, const char*, const char*, const char*);
	//criticality& operator=(const criticality&) = 0;
	//criticality(const criticality&) =0;
	arma::mat read_matlab_matrix(const char*);
	unsigned int  eval_criticality(std::vector<unsigned int>& x, std::string&);
	unsigned int  measurement_criticality(std::vector<unsigned int> x);
	unsigned int  top_branch_criticality(std::vector<unsigned int>& x);
	unsigned int  bd_branch_criticality(std::vector<unsigned int>& x);
	unsigned int  munit_criticality(std::vector<unsigned int> x);
	unsigned int  complete_munit_criticality(std::vector<unsigned int>& x);
	unsigned int  munit_observability_analysis(std::vector<unsigned int> y, arma::mat A);
	unsigned int  observability_analysis(arma::mat, double tol = 1e-10);
	unsigned int  munit_observability_analysis(std::vector<int>, arma::mat);
	std::size_t get_nm() { return nm; }
	std::size_t get_ns() { return ns; }
	std::size_t get_mu_size() { return mu_size; }
	std::vector<std::size_t> get_mu_location() { return mu_location; }
	std::vector<std::size_t> get_meas_location() { return meas_location; }
	std::stack<std::vector<unsigned int>> get_meas_ck() { return meas_ck; }
	std::stack<std::vector<unsigned int>> get_mu_ck() { return mu_ck; }
	double get_det() { return arma::det(U); }
};


