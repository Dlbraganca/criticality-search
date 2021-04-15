#include"./headers/optimized_hillclimbing.h"


Optimized_HillClimbing::Optimized_HillClimbing(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {
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
void Optimized_HillClimbing::main(){
	bool loopControl = true;
	unsigned int count = 0;
	unsigned int ckFound = 0;
	std::stack<std::vector<unsigned int>> searchResult;
	//min performance 10
	while (perfomanceTest > 0.1 || loopControl )
	{
		loopControl = false;
		std::vector<systemState> newPopulation = create_population(); //tem q ser nao observavel
		for (size_t i = 0; i < newPopulation.size(); i++)
		{
			std::cout << "A* INICIADA......\n";
			local_asearch search = local_asearch(newPopulation[i], critical_data, get_crit_type()); //busca apenas com as medidas escolhidas da tupla
			std::cout << "A* EXECUTADA\n";
			searchResult = search.get_result();
			ckFound = ckFound + result_evaluation(searchResult); //(hill climbing so pra que encontrou mais)
			count++;
		}
		std::cout << "ck: " << ckFound << "\n";
		perfomanceTest = double(ckFound) / count;
		std::cout << "performance: "<< perfomanceTest << "\n";
		no_of_visited_solutions++;	
	}
	convertResult(); //converte a tabela hash para o lopt
	report();
}

void Optimized_HillClimbing::convertResult() {
	for (auto it = ckList.cbegin(); it != ckList.cend(); ++it) {
		lopt.push(it->second);
	}
}

unsigned int Optimized_HillClimbing::result_evaluation(std::stack<std::vector<unsigned int>> searchResult) {
	std::string hashKey;
	unsigned int count = 0;
	while (!searchResult.empty())
	{
		hashKey = get_hash(searchResult.top());
		if (ckList.find(hashKey) == ckList.end())//caso a ck nao esteja na tabela de resultados, insere 
		{
			ckList.emplace(hashKey, searchResult.top());
			std::cout << "nova ck inserida!\n";
			count++;
		}
		searchResult.pop();
	}
	return count;
}

std::vector<systemState> Optimized_HillClimbing::create_population() {

	std::vector<systemState> population;
	std::vector<unsigned int> initialVector;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	if (get_crit_type() == "measurement")
	{
		/*std::vector<unsigned int> newVector;
		for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
		{
			newVector.push_back(1);
		}
		systemState newState(newVector, critical_data, get_crit_type());
		population.push_back(newState);*/
		while (population.size() != populationSize)
		{
			for (size_t i = 0; i < critical_data.get_meas_location().size(); i++)
			{
				std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
				int randNum = distribution(generator); //gera o numero aleatorio
				initialVector.push_back(randNum);
			}
			systemState newState(initialVector, critical_data, get_crit_type());
			if (newState.get_heuristic() == 0)
			{
				population.push_back(newState);
			}
			initialVector.clear();
		}
	}
	else
	{
		while (population.size() != populationSize)
		{
			for (size_t i = 0; i < critical_data.get_mu_location().size(); i++)
			{
				std::uniform_int_distribution <int> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
				int randNum = distribution(generator); //gera o numero aleatorio
				initialVector.push_back(randNum);
			}
			systemState newState(initialVector, critical_data, get_crit_type());
			if (newState.get_heuristic() == 0)
			{
				population.push_back(newState);
			}
			initialVector.clear();
		}
	}
	std::cout << "NOVA POPULACAO\n";
	for (size_t i = 0; i < population.size(); i++)
	{
		for (size_t j = 0; j < population[i].get_cklist().size(); j++)
		{
			std::cout << population[i].get_cklist()[j];
		}
		std::cout<< std::endl;
	}
	return population;
}


void Optimized_HillClimbing::report() {

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