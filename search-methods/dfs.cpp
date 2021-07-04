#include"./headers/dfs.h"

dfs::dfs(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {
	main();
	report();
}

//dfs::dfs(systemState SYSTEM, criticality& CRITICAL_DATA, std::string CK_PARAM_FILE) {
//	ck_param_file = CK_PARAM_FILE;
//	critical_data = CRITICAL_DATA;
//	system = SYSTEM;
//	main();
//}


//systemState dfs::get_best_heuristic(std::vector<systemState>& pile) {
//	double bestHeuristic = pile.front().get_heuristic();
//	unsigned int interator = 0;
//	systemState result;
//	for (unsigned int i = 0; i < pile.size(); i++)
//	{
//		if (pile[i].get_heuristic() <= bestHeuristic)
//		{
//			bestHeuristic = pile[i].get_heuristic();
//			interator = i;
//		}
//	}
//	result = pile[interator];
//	pile.erase(pile.begin() + interator);
//	return result;
//}

void dfs::main() {
	std::stack<systemState> pile;
	systemState nextState;
	std::vector<unsigned int> atualMeasurement;
	std::vector<unsigned int> newMeasuremet;
	std::unordered_map< std::string, std::vector<unsigned int> >visitedStates;
	std::ofstream  status_file;
	elapsed_time = clock();
	//inicia o vetor inicial com todas a medidas
	if (get_crit_type() == "measurement")
	{
		for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
		{
			atualMeasurement.push_back(0);
		}
	}
	else
	{
		for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
		{
			atualMeasurement.push_back(0);
		}
	}

	pile.push(systemState(atualMeasurement, critical_data, get_crit_type())); //estado inicial
	status_file.open("iteration_report_DFS.txt", std::ios::trunc);
	clock_t interation_time = clock();
	while (!pile.empty())
	{
		//std::cout << "tamanho da pilha: " << pile.size() << std::endl;
		//teste ordenar heuristica
		nextState = pile.top();
		pile.pop();
		atualMeasurement = nextState.get_cklist();

		//verifica se é o objetivo
		if (critical_data.measurement_criticality(atualMeasurement) == 1)
		{
			lopt.push(atualMeasurement);
			no_of_visited_solutions++;
			if (status_file.is_open()) { // impressao parametros do problema
				status_file << "n_estados_visitados: " << no_of_visited_solutions << " cks_encontradas: " << lopt.size() << " tempo_de_execucao: " << abs(elapsed_time - clock()) << " ms" << " tempo_da_iteracao: " << abs(interation_time - clock()) << " ms " << " memoria: " << get_memory() << "\n";
			}
			interation_time = clock();
			//std::cout << "k-tupla encontrada! " << result.size() << "\n";
		}
		//expande o nó atual 
		else
		{
			for (int i = atualMeasurement.size() - 1; i >= 0; i--)
			{
				if (atualMeasurement[i] == 1)
				{
					break;
				}
				else
				{
					newMeasuremet = atualMeasurement;
					newMeasuremet[i] = 1;
					systemState newState(newMeasuremet, critical_data, get_crit_type(), nextState); //novo estado criado
					if (newState.evalueCK(get_crit_type()))
					{
						pile.push(newState);
					}
				}
			}
			//std::cout << "pilha sorteada!\n";
			//for (size_t i = 0; i < pile.size(); i++)
			//{
			//	std::cout << pile[i].get_heuristic() << std::endl;
			//}
		}
	}
	status_file.close();
}

void dfs::report() {

	std::ofstream critfile, report_file;
	std::vector<unsigned int> tuple;
	int result;

	critfile.open("critical_tuples_dfs.txt", std::ios::trunc);
	report_file.open("BB_report_dfs.txt");
	if (report_file.is_open()) { // impressao parametros do problema
		report_file << "Parametros do problema \n" << std::endl;
		report_file << "Dimensao:" << dim << std::endl;
		report_file << "k-limite:" << klim << std::endl;
		report_file << "k-min:" << kmin << std::endl;
		report_file << "k-max:" << kmax << std::endl;
		report_file << "Criticalidade:" << get_crit_type() << std::endl;
		report_file << "Tipo de busca:" << get_search_method() << std::endl;
		report_file << "no. solucoes visitadas:" << no_of_visited_solutions << std::endl;
		report_file << "tempo decorrido:" << elapsed_time << std::endl;
		report_file << "memória utilizada:" << get_memory() << std::endl;
	}
	if (critfile.is_open()) { // impressao das tuplas criticas
		while (!lopt.empty()) {
			tuple = lopt.top(); // get stack top element		
			lopt.pop(); // pop stack
			for (std::vector<unsigned int>::iterator it = tuple.begin(); it != tuple.end(); ++it) {
				critfile << *it << " ";
			}
			critfile << std::endl;
		}
		critfile.close();
		std::cout << "critical tuples file successfully generated !!!!" << std::endl;
	}
	else
	{
		std::cout << "Unable to print the critical tuples" << std::endl;
	}
	result = remove("active_subsets.temp");// limpeza dos arquivos temporarios
	result = remove("critical_list.temp");// limpeza dos arquivos temporarios
	result = remove("temp_report.temp");// limpeza dos arquivos temporarios
};