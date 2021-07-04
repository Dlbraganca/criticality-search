//#define USE_FAST_CRITICALITY_H 1
/*#include "criticality.h"
#include "ck_search.h"
#include "bb_ck.h"
*/
#include"./search-methods/headers/hill_climbing.h"
#include"./search-methods/headers/simulated_annealing.h"
#include"./search-methods/headers/optimized_hillclimbing.h"
#include"./search-methods/headers/optimized_dfs.h"
#include"./search-methods/headers/reverse_dfs.h"
#include"./search-methods/headers/successive_hill_climbing.h"
#include"./search-methods/headers/reverse_hill_climbing.h"
#include"./search-methods/headers/dfs.h"
#include"./search-methods/headers/random_start_a_search.h"

void main() {


	std::ifstream parameters_file("ck_directives.txt", std::ios_base::in);
	std::string param_str;
	if (parameters_file.is_open()) {
		std::cout << "Parameter file has been successfully opened. Reading search method ...";
		getline(parameters_file, param_str);
		parameters_file.close();
		std::cout << "Done !!!" << std::endl;
	}
	else
	{
		std::cout << "Unable to open the search parameters file" << std::endl;
	}
	if (param_str.compare("hill_climbing") == 0) {
		HillClimbing search = HillClimbing("ck_directives.txt");
	}
	else if (param_str.compare("simulated_annealing") == 0) {
		SimulatedAnnealing search = SimulatedAnnealing("ck_directives.txt");
	}
	else if (param_str.compare("optimized_hillclimbing") == 0) {
		Optimized_HillClimbing search = Optimized_HillClimbing("ck_directives.txt");
	}
	else if (param_str.compare("optimized_dfs") == 0) {
		Optimized_DFS search = Optimized_DFS("ck_directives.txt");
	}
	else if (param_str.compare("reverse_dfs") == 0) {
		reverse_dfs search = reverse_dfs("ck_directives.txt");
	}
	else if (param_str.compare("successive_hill_climbing") == 0) {
		successive_hill_climbing search = successive_hill_climbing("ck_directives.txt");
	}
	else if (param_str.compare("reverse_hill_climbing") == 0) {
		reverse_hill_climbing search = reverse_hill_climbing("ck_directives.txt");
	}
	else if (param_str.compare("dfs") == 0) {
		dfs search = dfs("ck_directives.txt");
	}
	else if (param_str.compare("random_start_a_search") == 0) {
		random_start_a_search search = random_start_a_search("ck_directives.txt");
	}
	};