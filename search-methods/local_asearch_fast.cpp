#include"./headers/local_asearch_fast.h"

local_asearch_fast::local_asearch_fast(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE) {

}

local_asearch_fast::local_asearch_fast(systemState SYSTEM, criticality& CRITICAL_DATA, std::string CK_PARAM_FILE) {
	ck_param_file = CK_PARAM_FILE;
	critical_data = CRITICAL_DATA;
	system = SYSTEM;
	main();
}

//bool comparar_heuristicas(systemState& a, systemState& b) {
//	return a.get_f() > b.get_f(); //descendente
//};
//
//void sort_vector(std::vector<systemState>& x) {
//	std::sort(x.begin(), x.end(), &comparar_heuristicas);
//};


systemState local_asearch_fast::get_best_heuristic(std::vector<systemState>& pile) {
	double bestF = pile.front().get_f();
	unsigned int interator = 0;
	systemState result;
	for (unsigned int i = 0; i < pile.size(); i++)
	{
		if (pile[i].get_f() <= bestF)
		{
			bestF = pile[i].get_f();
			interator = i;
		}
	}
	result = pile[interator];
	pile.erase(pile.begin() + interator);
	return result;
}

systemState local_asearch_fast::fast_sort() {
	double bestF = std::numeric_limits<double>::max(); //pegar a menor heuristica entao iniciamos com o maior valor
	unsigned int positionBest = 0;
	systemState bestState;
	bool foundTemporaryPile = false;
	bool foundPile = false;
	//std::cout << "heuristica da pilha : \n";
	for (unsigned int i = 0; i < pile.size(); i++) //avalia na pilha
	{
		//std::cout << pile[i].get_f() << std::endl;
		if (pile[i].get_f() < bestF)
		{
			bestState = pile[i];
			bestF = bestState.get_f();
			positionBest = i;
			foundPile = true;
		}
	}
	//std::cout << "heuristica da pilha temporaria: \n";
	for (unsigned int i = 0; i < temporaryPile.size(); i++)//avalia entre os novos estados
	{
		//std::cout << temporaryPile[i].get_f() << std::endl;
		if (temporaryPile[i].get_f() < bestF) 
		{
			bestState = temporaryPile[i];
			bestF = bestState.get_f();
			positionBest = i;
			foundTemporaryPile = true;
		}
	}

	if (foundTemporaryPile) //se a melhor heurisitica foi encontrada na pilha temporaria
	{
		temporaryPile[positionBest].set_f(std::numeric_limits<double>::max());
	}
	else if(foundPile) //se a melhor heurisitica foi encontrada na pilha
	{
		pile[positionBest].set_f(std::numeric_limits<double>::max());//seta o valor desse estado com a maior heuristica possivel (busca-se a menor heuristica)
		freePosition.push_back(positionBest); // adiciona essa posicao no vetor com as posicoes livres
	}
	while (!temporaryPile.empty())
	{
		if (temporaryPile.back().get_f() < std::numeric_limits<double>::max())
		{
			if (!freePosition.empty())
			{
				unsigned int position = freePosition.back();
				freePosition.pop_back();
				pile[position] = temporaryPile.back();
				temporaryPile.pop_back();
			}
			else
			{
				pile.push_back(temporaryPile.back());
				temporaryPile.pop_back();
			}
		}
		else
		{
			temporaryPile.pop_back();
		}
	}
	//std::cout << "heuristica escolhida : " << bestState.get_f() << std::endl;
	if (bestState.get_cklist().empty()) //quando a pilha ta limpa so ira existir heuristicas com o valor maximo e por isso o melhor resultado sera o vazio
	{
		pile.clear();
	}
	return bestState;
}

void local_asearch_fast::main() {
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
	//pile.push_back(systemState(newMeasuremet, critical_data, ck_param_file));
	nextState = systemState(newMeasuremet, critical_data, ck_param_file);
	//status_file.open("status_reportA_fast.txt", std::ios::trunc);
	while (!nextState.get_cklist().empty() && metric > stoppingCriterion)
	{
		//std::cout << "tamanho da pilha: " << pile.size() << std::endl;
		//teste ordenar heuristica
		no_of_visited_solutions++;
		clock_t interation_time = clock();
		atualMeasurement = nextState.get_cklist();
		//verifica se é o objetivo
		if (critical_data.measurement_criticality(atualMeasurement) == 1)
		{
			result.push(atualMeasurement);
			metric = double(result.size()) / double(no_of_visited_solutions);
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
				else if (referenceVector[i] == 1)
				{
					newMeasuremet = atualMeasurement;
					newMeasuremet[i] = 1;
					systemState newState(newMeasuremet, critical_data, ck_param_file, nextState);
					if (newState.evalueCK())
					{
						temporaryPile.push_back(newState);
					}
				}
			}
		}
		nextState = fast_sort();
		//if (status_file.is_open()) { // impressao parametros do problema
		//	status_file << "n_estados_visitados: " << no_of_visited_solutions << " cks_encontradas: " << result.size() << " tempo_de_execucao: " << abs(elapsed_time - clock()) << " ms" << " tempo_da_iteracao: " << abs(interation_time - clock()) << " ms " << " memoria: " << get_memory() << "\n";
		//}
	}
	status_file.close();
}