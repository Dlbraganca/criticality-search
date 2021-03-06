#include"./headers/local_asearch.h"

local_asearch::local_asearch(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {

}

local_asearch::local_asearch(systemState SYSTEM, criticality& CRITICAL_DATA , std::string CK_PARAM_FILE) {
	ck_param_file = CK_PARAM_FILE;
	critical_data = CRITICAL_DATA;
	system = SYSTEM;
	main();
}

bool comparar_heuristicas(systemState& a, systemState& b) {
	return a.get_heuristic() > b.get_heuristic(); //descendente
};

void sort_vector(std::vector<systemState>& x) {
	std::sort(x.begin(), x.end(), &comparar_heuristicas);
};


systemState local_asearch::get_best_heuristic(std::vector<systemState> &pile) {
	double bestHeuristic = pile.front().get_heuristic();
	unsigned int interator = 0;
	systemState result;
	for (unsigned int i = 0; i < pile.size(); i++)
	{
		if (pile[i].get_heuristic() <= bestHeuristic)
		{
			bestHeuristic = pile[i].get_heuristic();
			interator = i;
		}
	}
	result = pile[interator];
	pile.erase(pile.begin() + interator);
	return result;
}

void local_asearch::main() {
	std::vector<systemState> pile;
	std::string hashKey;
	systemState nextState;
	std::vector<unsigned int> atualMeasurement;
	std::vector<unsigned int> newMeasuremet;
	std::vector<unsigned int> referenceVector = system.get_cklist(); //vetor contendo as medidas que podem ser manipuladas
	std::unordered_map< std::string, std::vector<unsigned int> >visitedStates;
	std::ofstream  status_file;
	elapsed_time = clock();
	//inicia o vetor inicial com todas a medidas
	for (size_t i = 0; i < referenceVector.size(); i++)
	{
		newMeasuremet.push_back(0);
	}

	pile.push_back(systemState(newMeasuremet, critical_data, ck_param_file));

	status_file.open("status_reportA.txt", std::ios::trunc);
	while (!pile.empty())
	{
		//std::cout << "tamanho da pilha: " << pile.size() << std::endl;
		//teste ordenar heuristica
		no_of_visited_solutions++;
		clock_t interation_time = clock();
		sort_vector(pile);
		nextState = pile.back();
		pile.pop_back();
		atualMeasurement = nextState.get_cklist();
		
		//verifica se ? o objetivo
		if (critical_data.measurement_criticality(atualMeasurement) == 1)
		{
			result.push(atualMeasurement);
			//std::cout << "k-tupla encontrada! " << result.size() <<  "\n";
		}
		//expande o n? atual 
		else
		{
			for (int i = atualMeasurement.size() - 1; i >= 0; i--)
			{
				if (atualMeasurement[i] == 1)
				{
					break;
				}
				else if (referenceVector[i] == 1)
				{
					newMeasuremet = atualMeasurement;
					newMeasuremet[i] = 1;
					systemState newState(newMeasuremet, critical_data, ck_param_file);
					if (newState.evalueCK())
					{
						pile.push_back(newState);
					}
				}
			}
			//std::cout << "pilha sorteada!\n";
			//for (size_t i = 0; i < pile.size(); i++)
			//{
			//	std::cout << pile[i].get_heuristic() << std::endl;
			//}
		}
		if (status_file.is_open()) { // impressao parametros do problema
			status_file << "n_estados_visitados: " << no_of_visited_solutions << " cks_encontradas: " << result.size() << " tempo_de_execucao: " << abs(elapsed_time - clock()) << " ms" << " tempo_da_iteracao: " << abs(interation_time - clock()) << " ms " << " memoria: " << get_memory() << "\n";
		}
	}
	status_file.close();
}