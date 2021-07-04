#include"./headers/random_start_a_search.h"


random_start_a_search::random_start_a_search(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {
	std::vector<unsigned int> initialVector;
	//inicia vetor com todas as medidas do sistema
	main();
}

/// <summary>
/// Resultados:
/// como a populacao inicial é feita por tuplas nao-observáveis,
/// a tendência é a populacao apresentar tuplas de alta cardinalidade e, por isso,
/// a árvore resultante é mt grande consumindo mais tempo que se fosse apenas 1 árvore
///
/// </summary>
void random_start_a_search::main() {
	bool loopControl = true;
	clock_t tbegin = clock();
	unsigned int count = 0;
	unsigned int ckFound = 0;
	std::stack<std::vector<unsigned int>> searchResult;
	std::ofstream status_file;
	status_file.open("iteration_report_random_a_search.txt", std::ios::trunc);
	//min performance 10
	//status_file.open("iteration_report_abel.txt", std::ios::trunc);
	while (perfomanceTest > 0.05 || loopControl)
	{
		clock_t interation_time = clock();
		no_of_visited_solutions++;
		loopControl = false;
		std::vector<systemState> newPopulation = create_population(); //tem q ser nao observavel
		for (size_t i = 0; i < newPopulation.size(); i++)
		{
			//std::cout << "A* INICIADA......\n";
			//local_asearch search_0 = local_asearch(newPopulation[i], critical_data, get_crit_type()); //busca apenas com as medidas escolhidas da tupla
			//std::cout << "A* RAPIDA INICIADA......\n";
			a_search_random search = a_search_random(newPopulation[i], critical_data, get_crit_type()); //busca apenas com as medidas escolhidas da tupla
			//std::cout << "DFS INICIADA......\n";
			//local_dfs search_1 = local_dfs(newPopulation[i], critical_data, get_crit_type()); //busca apenas com as medidas escolhidas da tupla
			//std::cout << "BFS INICIADA......\n";
			//local_bfs search_2 = local_bfs(newPopulation[i], critical_data, get_crit_type()); //busca apenas com as medidas escolhidas da tupla
			//std::cout << "A* EXECUTADA\n";
			searchResult = search.get_result();
			ckFound = ckFound + result_evaluation(searchResult); //(hill climbing so pra que encontrou mais)
			count++;
		}
		//std::cout << "ck: " << ckFound << "\n";
		perfomanceTest = (double(ckFound) + 1.0) / count;
		//std::cout << "performance: "<< perfomanceTest << "\n";
		if (status_file.is_open()) { // impressao parametros do problema
			status_file << "n_estados_visitados: " << no_of_visited_solutions << " cks_encontradas: " << ckFound << " tempo_de_execucao: " << abs(elapsed_time - clock()) << " ms" << " tempo_da_iteracao: " << abs(interation_time - clock()) << " ms " << " memoria: " << get_memory() << "\n";
		}
	}
	elapsed_time = clock() - tbegin;
	convertResult(); //converte a tabela hash para o lopt
	report();
}

void random_start_a_search::convertResult() {
	for (auto it = ckList.cbegin(); it != ckList.cend(); ++it) {
		lopt.push(it->second);
	}
}

unsigned int random_start_a_search::result_evaluation(std::stack<std::vector<unsigned int>> searchResult) {
	std::string hashKey;
	unsigned int count = 0;
	while (!searchResult.empty())
	{
		hashKey = get_hash(searchResult.top());
		if (ckList.find(hashKey) == ckList.end())//caso a ck nao esteja na tabela de resultados, insere 
		{
			ckList.emplace(hashKey, searchResult.top());
			//std::cout << "nova ck inserida!\n";
			count++;
			/*for (size_t i = 0; i < searchResult.top().size(); i++)
			{
				std::cout << searchResult.top()[i] << " ";
			}
			std::cout  << "\n";*/
		}
		searchResult.pop();
	}
	return count;
}

std::vector<systemState> random_start_a_search::create_population() {

	std::vector<systemState> population;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	if (get_crit_type() == "measurement")
	{
		std::vector< unsigned int> initialVector(critical_data.get_meas_location().size(), 0);
		//std::cout << "size vector : " << critical_data.get_meas_location().size() << std::endl;
		double p = 1.0 / critical_data.get_meas_location().size();
		//std::cout << "p : " << p << std::endl;
		std::geometric_distribution <int> distribution(p); // cria uma distribuicao uniforme com os valores min e max 
		int randNum;
		int maxValue = (critical_data.get_nm() - critical_data.get_ns()) + 1;
		do {
			randNum = distribution(generator); //gera o numero aleatorio
		} while (randNum > maxValue || randNum <= 0);
		//std::cout << "numero sorteado: " << randNum << std::endl;
		int countOne = 0;
		//randNum = 19;
		//std::cout << "profundidade sorteada: " << randNum << std::endl;
		while (countOne < randNum)
		{
			std::uniform_int_distribution <int> distribution_uniform(0, critical_data.get_meas_location().size() - 1); // cria uma distribuicao uniforme com os valores min e max 
			int randPosition = distribution_uniform(generator);
			if (initialVector[randPosition] == 0)
			{
				initialVector[randPosition] = 1;
				countOne++;
			}
		}
		systemState newState(initialVector, critical_data, get_crit_type());
		population.push_back(newState);
	}
	else
	{
		std::vector< unsigned int> initialVector(critical_data.get_mu_location().size(), 0);
		double p = 0.6 / critical_data.get_mu_location().size();
		//std::cout << "p : " << p;
		std::geometric_distribution <int> distribution(p); // cria uma distribuicao uniforme com os valores min e max 
		int randNum = distribution(generator); //gera o numero aleatorio
		//std::cout << "numero sorteado: " << randNum << std::endl;
		int countOne = 0;
		while (countOne < randNum)
		{
			std::uniform_int_distribution <int> distribution_uniform(0, critical_data.get_mu_location().size()); // cria uma distribuicao uniforme com os valores min e max 
			int randPosition = distribution_uniform(generator) - 1;
			if (initialVector[randPosition] == 0)
			{
				initialVector[randPosition] = 1;
				countOne++;
			}
		}
		systemState newState(initialVector, critical_data, get_crit_type());
		population.push_back(newState);
	}
	/*std::cout << "NOVA POPULACAO\n";
	for (size_t i = 0; i < population.size(); i++)
	{
		for (size_t j = 0; j < population[i].get_cklist().size(); j++)
		{
			std::cout << population[i].get_cklist()[j];
		}
		std::cout<< std::endl;
	}*/
	return population;
}


void random_start_a_search::report() {

	std::ofstream critfile, report_file;
	std::vector<unsigned int> tuple;
	int result;

	critfile.open("critical_tuples_random_a_search.txt", std::ios::trunc);
	report_file.open("BB_report_random_a_search.txt");
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