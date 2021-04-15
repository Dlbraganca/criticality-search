#include"./headers/reverse_hill_climbing.h"


reverse_hill_climbing::reverse_hill_climbing() {};

reverse_hill_climbing::reverse_hill_climbing(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE)
{
	main();
	convert_result();
	report();
};

reverse_hill_climbing::~reverse_hill_climbing() {};

systemState reverse_hill_climbing::highest_value(systemState current) { // funcao que retorna o maior valor disponivel

	std::vector<unsigned int> atualList;
	std::vector<int> lastMovements;
	std::vector<systemState> states;
	std::vector<systemState> queue;
	double atualHeuristic;
	systemState bestState;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	bool kTuple = true;
	bool endLine = false;

	atualList = current.get_cklist();
	//std::cout << "------nova profundidade----\n";
	//cria a pilha fifo de proximo estados
	for (size_t i = 0; i < atualList.size(); i++)
	{
		double heuristic = current.get_heuristic();
		std::vector<unsigned int> newState;
		if (atualList[i] == 1)
		{
			newState = atualList;
			newState[i] = 0;
			systemState state = systemState(newState, critical_data, get_crit_type());
			if (state.get_heuristic() == 0 || state.get_heuristic() == std::numeric_limits<double>::max()) //lembrar que a classe sytemState ja ta fazendo o teste n-1 tornando o sistema mais lento essa verificacao nao precisa
			{
				kTuple = false;
				if (evalue_new_tuple(state))
				{
					queue.push_back(state);
				}
			}
		}
	}
	if (kTuple)
	{
		current.set_heuristic(-1);// -1 de heuristica siginifica q é uma tupla critica
		ktuplefound++;
		std::cout << "ktupla encontrada "<< ktuplefound << "\n";
		return current;
	}
	else if (queue.size() > 0)
	{
		std::uniform_int_distribution <int> distribution(0, queue.size() - 1); // cria uma distribuicao uniforme com os valores do vetor
		int randNum = distribution(generator); //gera o numero aleatorio
		return queue[randNum]; //siginifica q a tupla possui subtuplas e retorna uma tupla aleatoria
	}
	else
	{
		current.set_heuristic(-20);// -20 de heuristica siginifica q é uma tupla critica
		std::cout << "fim da árvore\n";
		return current;
	}
}

bool reverse_hill_climbing::evalue_new_tuple(systemState atual) {

	unsigned int deepth = atual.get_deepth();
	std::vector<unsigned int> evalueState = atual.get_cklist();

	std::vector<std::vector<unsigned int>>  list = ckList[deepth];

	for (size_t i = 0; i < list.size(); i++)
	{
		unsigned int equalCounter = 0;
		std::vector<unsigned int> state = list[i];
		for (size_t j = 0; j < state.size(); j++)
		{
			if (state[j] == 1 && evalueState[j] == 1)
			{
				equalCounter++;
			}
		}
		if (equalCounter == deepth)
		{
			return false;
		}
	}
	return true;  //tupla nao contem uma k-tupla critica
}

void reverse_hill_climbing::main() {

	std::vector<unsigned int> initialVector;
	std::vector<systemState> pile;
	unsigned int contadorPrint = 0;

	if (get_crit_type() == "measurement")
	{
		for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
		{
			initialVector.push_back(1);
		}
	}
	else
	{
		for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
		{
			initialVector.push_back(1);
		}
	}

	systemState neighbor;
	std::vector<unsigned int> result;
	bool loopControl2 = true;
	double stoppingCriterion = 1;
	while ((stoppingCriterion/(no_of_visited_solutions+1)) > 0.01)
	{
		std::cout << "valor de convergencia " << stoppingCriterion / (no_of_visited_solutions + 1) << "\n";
		systemState current = systemState(initialVector, critical_data, get_crit_type()); //define a corrente como estado inicial
		//systemState current = create_population();
		result.clear();
		bool loopControl = true;
		no_of_visited_solutions++;
		while (loopControl)
		{
			neighbor = highest_value(current);
			if (neighbor.get_heuristic() == -1)
			{
				save_result(neighbor.get_cklist());
				stoppingCriterion++;
				loopControl = false;

			}
			else if(neighbor.get_heuristic() == -20)
			{
				loopControl = false;
			}
			else
			{
				current = neighbor;
			}
		}
	}
	std::cout << "busca encerrada \n";
	elapsed_time = clock() - elapsed_time;
}


systemState reverse_hill_climbing::create_population() {

	std::vector<unsigned int> initialVector;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	bool loopControl = true;
	systemState result;
	while (loopControl)
	{
		if (get_crit_type() == "measurement")
		{
			double deepthControl = 1;
			for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
			{
				std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
				int randNum = distribution(generator); //gera o numero aleatorio
				if (randNum / deepthControl >= 0.99)
				{
					initialVector.push_back(1);
					deepthControl++;
				}
				else
				{
					initialVector.push_back(0);
				}
			}
			systemState newState(initialVector, critical_data, get_crit_type());
			if (newState.get_heuristic() != 0 && newState.get_heuristic() != std::numeric_limits<double>::max())
			{
				result = newState;
				loopControl = false;
			}
			initialVector.clear();
		}
		else
		{
			for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
			{
				std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
				int randNum = distribution(generator); //gera o numero aleatorio
				initialVector.push_back(randNum);
			}
			systemState newState(initialVector, critical_data, get_crit_type());
			if (newState.get_heuristic() != 0)
			{
				result = newState;
				loopControl = false;
			}
			initialVector.clear();
		}
	}
	return result;
}

void reverse_hill_climbing::save_result(std::vector<unsigned int> state) {
	unsigned int deepth = 0;
	for (size_t i = 0; i < state.size(); i++)
	{
		if (state[i] == 1)
		{
			deepth++;
		}
	}
	if (deepth > 0)
	{
		ckList[deepth].push_back(state);
	}
}

void reverse_hill_climbing::convert_result() {
	for (auto it = ckList.begin(); it != ckList.end(); ++it) {
		std::vector<std::vector<unsigned int>> result = it->second;
		while (!result.empty())
		{
			lopt.push(result.back());
			result.pop_back();
		}
	}
	ckList.clear();
}

void reverse_hill_climbing::report() {

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