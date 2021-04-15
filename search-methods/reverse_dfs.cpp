#include"./headers/reverse_dfs.h"


reverse_dfs::reverse_dfs(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {
	std::vector<unsigned int> initialVector;
	//inicia vetor com todas as medidas do sistema
	search();
}


void reverse_dfs::search() {
	bool loopControl = true;
	std::string hashKey;
	std::vector<unsigned int> atualState;
	std::unordered_map < std::string, bool> visitedStates;
	std::stack<std::vector<unsigned int>> pile;
	pile.push(create_population());

	hashKey = get_hash(pile.top());
	visitedStates.emplace(hashKey, true);
	bool newStatesFound = false;
	elapsed_time = clock();
	while (!pile.empty())
	{
		unsigned int count = 0;
		no_of_visited_solutions++;
		atualState = pile.top();
		pile.pop();
		newStatesFound = false;
		for (unsigned int i = 0 ; i < atualState.size(); i++)
		{
			if (atualState[i] == 1)
			{
				std::vector<unsigned int> newState = atualState;
				newState[i] = 0;
				hashKey = get_hash(newState);
				if (visitedStates.find(hashKey) == visitedStates.end()) //caso a nova tupla nao esteja na lista de visitados
				{
					if (get_crit_type() == "measurement")
					{
						if (critical_data.measurement_criticality(newState) == 1) //checa a observabilidade
						{//caso seja nao-observavel
							pile.push(newState); //insere na lista
							visitedStates.emplace(hashKey, true); //insere na tabela de estados visitados como nao observavel
							count++; //adiciona pro contador de sub-tuplas nao observaveis
						}
						else
						{//caso seja observavel 
							visitedStates.emplace(hashKey, false); // adiciona a lista de estados visitados como observavel
						}
					}
					else
					{
						if (critical_data.munit_criticality(newState) == 1)
						{
							pile.push(newState);
							count++;
						}
						else
						{
							visitedStates.emplace(hashKey, false);
						}
					}
				}
				else
				{// se estiver na lista de estados visitados
					if (visitedStates[hashKey]) // se a sub-tupla for critica
					{
						count++;//adiciona 1 no contador de sub-tuplas criticas
					}
				}
			}
		}
		if (count == 0) //caso a tupla nao contenha nenhuma sub-tupla critica
		{
			lopt.push(atualState); //adiciona na lista de resposta
		}
		//std::cout << "quantidade de solucoes: " << lopt.size() << " pilha: " << pile.size() << std::endl;
	}
	elapsed_time = clock() - elapsed_time;
	report();
}

void reverse_dfs::convertResult() {
	for (auto it = ckList.cbegin(); it != ckList.cend(); ++it) {
		lopt.push(it->second);
	}
}

void reverse_dfs::result_evaluation(std::vector<unsigned int> searchResult) {
	std::string hashKey;

	hashKey = get_hash(searchResult);
	if (ckList.find(hashKey) == ckList.end())//caso a ck nao esteja na tabela de resultados, insere 
	{
		ckList.emplace(hashKey, searchResult);
	}
}

std::vector<unsigned int> reverse_dfs::create_population() {

	std::vector<unsigned int> initialVector;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	if (get_crit_type() == "measurement")
	{
		for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
		{
			initialVector.push_back(1);
		}
		systemState newState(initialVector, critical_data, get_crit_type());
	}
	else
	{
		for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
		{
			initialVector.push_back(1);
		}
		systemState newState(initialVector, critical_data, get_crit_type());
	}

	return initialVector;
}


void reverse_dfs::report() {

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