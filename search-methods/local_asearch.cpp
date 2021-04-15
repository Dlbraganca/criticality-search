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


void local_asearch::main() {
	std::vector<systemState> pile;
	std::string hashKey;
	systemState nextState;
	std::vector<unsigned int> atualMeasurement;
	std::vector<unsigned int> newMeasuremet;
	std::vector<unsigned int> referenceVector = system.get_cklist(); //vetor contendo as medidas que podem ser manipuladas
	std::unordered_map< std::string, std::vector<unsigned int> >visitedStates;
	

	//determina se o estado atula é uma tupla critica -> se sim termina a busca
	if (system.get_heuristic() == 0 && system.evalueCK())
	{
		result.push(pile.back().get_cklist());
		std::cout << "ck-tupla encontrada!\n";
	}
	else //-> se nao inicia a busca
	{
		for (size_t i = 0; i < referenceVector.size(); i++)//inicia o vetor inicial com todas a medidas
		{
			newMeasuremet.push_back(0);
		}
		pile.push_back(systemState(newMeasuremet, critical_data, ck_param_file));
		while (!pile.empty())
		{
			//std::cout << "tamanho da pilha: " << pile.size() << std::endl;
			sort_vector(pile);
			nextState = pile.back();
			pile.pop_back();
			atualMeasurement = nextState.get_cklist();

			//determina se o estado atual é uma tupla critica
			for (size_t i = 0; i < atualMeasurement.size(); i++)
			{
				if (atualMeasurement[i] == 0 && referenceVector[i] == 1)
				{
					newMeasuremet = atualMeasurement;
					newMeasuremet[i] = 1;
					systemState newState(newMeasuremet, critical_data, ck_param_file);
					hashKey = get_hash(newState.get_cklist());
					if (visitedStates.find(hashKey) == visitedStates.end())
					{
						visitedStates.emplace(hashKey, newState.get_cklist());
						if (newState.evalueCK())
						{
							if (critical_data.measurement_criticality(newState.get_cklist()) == 1)
							{
								result.push(newState.get_cklist());
								std::cout << "k-tupla encontrada!\n";
							}
							else
							{
								pile.push_back(newState);
							}
						}
					}
					hashKey = "";
				}
			}
			//std::cout << "pilha sorteada!\n";
			//for (size_t i = 0; i < pile.size(); i++)
			//{
			//	std::cout << pile[i].get_heuristic() << std::endl;
			//}
		}
	}
}