#include"./headers/optimized_dfs.h"


Optimized_DFS::Optimized_DFS(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {
	std::vector<unsigned int> initialVector;
	//inicia vetor com todas as medidas do sistema
	main();
}


void Optimized_DFS::main() {
	bool loopControl = true;
	unsigned int count = 0;
	unsigned int ckFound = 0;
	std::stack<std::vector<unsigned int>> searchResult;
	std::unordered_map < std::string, bool> visitedStates;
	//min performance 10

	systemState initalPopulation = create_population();
	std::stack<systemState> pile;

	pile.push(initalPopulation);

	while (!pile.empty())
	{
		std::vector<unsigned int> medState = pile.top().get_cklist();
		pile.pop();
		for (int i = medState.size() - 1; i >= 0; i--)
		{
			if (medState[i] == 1)
			{
				break;
			}
			else
			{
				std::vector<unsigned int> newMed = medState;
				newMed[i] = 1;
				if (visitedStates.find(get_hash(newMed)) == visitedStates.end() && ckList.find(get_hash(newMed)) == ckList.end())
				{
					visitedStates.emplace(get_hash(newMed), true);
					systemState newState(newMed, critical_data, get_crit_type());
					if (newState.get_heuristic() == 0)
					{
						std::cout << "hill climbing iniciada.....\n";
						newState = hill_climbing(newState);
						std::cout << "hill climbing realiada.....\n";
						result_evaluation(newState.get_cklist());
					}
					else
					{
						//adiciona na pilha
						pile.push(newState);
					}
				}
			}
		}
		no_of_visited_solutions++;
		std::cout << "quantidade de solucoes: " << ckList.size() << " pilha: " << pile.size() << std::endl;
	}
	convertResult(); //converte a tabela hash para o lopt
	report();
}

systemState Optimized_DFS::hill_climbing(systemState problem) {

	systemState maxState;
	std::queue<systemState> pile;
	pile.push(problem);
	systemState current;
	while (!pile.empty())
	{
		current = pile.front();
		pile.pop();
		for (size_t i = 0; i < current.get_cklist().size(); i++)
		{
			std::vector<unsigned int> newMed = current.get_cklist();
			if (newMed[i] == 1)
			{
				newMed[i] = 0;
				systemState newState(newMed, critical_data, get_crit_type());
				if (newState.get_heuristic() == 0)
				{
					pile.push(newState);
					break;
				}
			}
		}
	}
	return current;
}

void Optimized_DFS::convertResult() {
	for (auto it = ckList.cbegin(); it != ckList.cend(); ++it) {
		lopt.push(it->second);
	}
}

void Optimized_DFS::result_evaluation(std::vector<unsigned int> searchResult) {
	std::string hashKey;

	hashKey = get_hash(searchResult);
	if (ckList.find(hashKey) == ckList.end())//caso a ck nao esteja na tabela de resultados, insere 
	{
		ckList.emplace(hashKey, searchResult);
	}
}

systemState Optimized_DFS::create_population() {

	systemState population;
	std::vector<unsigned int> initialVector;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	if (get_crit_type() == "measurement")
	{
		for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
		{
			//std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
			//int randNum = distribution(generator); //gera o numero aleatorio
			initialVector.push_back(0);
		}
		systemState newState(initialVector, critical_data, get_crit_type());
		population = newState;
	}
	else
	{
		for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
		{
			//std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
			//int randNum = distribution(generator); //gera o numero aleatorio
			initialVector.push_back(0);
		}
		systemState newState(initialVector, critical_data, get_crit_type());
		population = newState;
	}

	return population;
}


void Optimized_DFS::report() {

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