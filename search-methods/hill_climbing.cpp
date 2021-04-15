#include"./headers/hill_climbing.h"


	HillClimbing::HillClimbing() {};
	
	HillClimbing::HillClimbing(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE)
	{	
		main();
		report();
	};

	HillClimbing::~HillClimbing() {};
	
	//systemState HillClimbing::get_result() {
	//	return result;
	//}

	bool HillClimbing::check_state(std::vector<unsigned int> state) {
		std::vector<std::vector<unsigned int>> statesToJump = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } };
		for (size_t i = 0; i < statesToJump.size(); i++)
		{
			for (size_t j = 0; j < statesToJump[i].size(); j++)
			{
				if (state[j] != statesToJump[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}

	systemState HillClimbing::highest_value(systemState current) { // funcao que retorna o maior valor disponivel

		std::vector<unsigned int> atualList;
		std::vector<int> lastMovements;
		std::vector<systemState> states;
		std::queue<systemState> queue;
		double atualHeuristic = 10000;
		systemState bestState;

		atualList = current.get_cklist();

		//cria a pilha fifo de proximo estados
		for (size_t i = 0; i < atualList.size(); i++)
		{
			if (atualList[i] == 0)
			{
				atualList[i] = 1;
			}
			if (check_state(atualList)) //exclui o vetor se pertecer a lista de proibidos !!!!TESTEEEEE!!!
			{
				systemState newState = systemState(atualList, critical_data, get_crit_type());
				if (newState.evalueCK())
				{
					queue.push(newState);
				}
			}
			atualList[i] = 0;
		}

		while (!queue.empty())
		{
			 atualHeuristic = queue.front().get_heuristic();
			 if (atualHeuristic < bestHeuristic)
			 {
				 bestHeuristic = atualHeuristic;
				 bestState = queue.front();
			 }
			 queue.pop();
		}
		return bestState;
	}

	void HillClimbing::main() {

		std::vector<unsigned int> initialVector;

		if (get_crit_type() == "measurement")
		{
			for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
			{
				initialVector.push_back(0);
			}
		}
		else
		{
			for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
			{
				initialVector.push_back(0);
			}
		}
		systemState current = systemState(initialVector, critical_data, get_crit_type()); //define a corrente como estado inicial
		systemState neighbor;
		bool loopControl = true;
		elapsed_time = clock();

		while (loopControl)
		{
			no_of_visited_solutions++;
			neighbor = highest_value(current);
			if (neighbor.get_heuristic() < current.get_heuristic())
			{
				loopControl = false;
			}
			current = neighbor;
		}
		//std::cout << "\nTEMPO MEDIO DE ITERACAO: " << tend / contador << std::endl;
		//std::cout << "TEMPO TOTAL DE EXECUCAO: " << tend << std::endl;
		//std::cout << "NUMERO DE ITERACOES: " << contador << std::endl;
		//std::cout << "MEMORIA UTILIZADA: " << get_memory() << std::endl;
		lopt.push(current.get_cklist());
		elapsed_time = clock() - elapsed_time;
	}

	void HillClimbing::report() {

		std::ofstream critfile, report_file;
		std::vector<unsigned int> tuple;
		int result;

		critfile.open("critical_tuples.txt", std::ios::trunc);
		report_file.open("BB_report.txt");
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