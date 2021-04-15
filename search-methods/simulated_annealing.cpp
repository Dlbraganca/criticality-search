//#include "8systemState.h"
#include"./headers/simulated_annealing.h"

	SimulatedAnnealing::SimulatedAnnealing(const char* CK_PARAM_FILE) : ck_search(CK_PARAM_FILE)
	{
		std::vector<unsigned int> initialVector;
		 //inicia vetor com todas as medidas do sistema
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
		systemState problem = systemState(initialVector, critical_data, get_crit_type());

		main(problem);
		report();
	}

	SimulatedAnnealing::~SimulatedAnnealing() {}

	systemState SimulatedAnnealing::get_result() { return result; }

	systemState SimulatedAnnealing::RandomValue(systemState current) { // funcao que retorna o menor valor disponivel

		std::vector<unsigned int> atualList;
		std::vector<systemState> queue;
		//unsigned int seed = clock() * 100000;
		//std::cout << "seed: " << seed << std::endl;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed); 


		atualList = current.get_cklist();
		//cria a pilha fifo de proximo estados
		for (size_t i = 0; i < atualList.size(); i++)
		{
			if (atualList[i] == 0)
			{
				atualList[i] = 1;
				systemState newState = systemState(atualList, critical_data, get_crit_type());
				if (newState.get_heuristic() == 0) //se a heuristica é 0 significa q é uma tupla critica
				{
					if (newState.evalueCK()) //checa pra saber se essa tupla contem uma tupla critica
					{
						queue.push_back(newState);
					}
				}
				else //caso nao insere nos novos movimentos
				{
					queue.push_back(newState);
				}
			}
			atualList[i] = 0;
		}
		if (queue.size() == 0)
		{
			throw 1;
		}
		else
		{
			std::uniform_int_distribution <int> distribution(0, queue.size() - 1); // cria uma distribuicao uniforme com os valores min e max 
			int randNum = distribution(generator); //gera o n�mero aleatorio
			return queue[randNum]; //retorna o movimento do numero aleatorio
		}
	}

	bool SimulatedAnnealing::RandomProbability(double delE, double T) { // funcao que retorna o menor valor disponivel


		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);

		//gerar aleatorio entre 0 e 1
		std::uniform_real_distribution <> distribution(0, 1); // cria uma distribuicao normal com os valores min e max 
		double randNum = distribution(generator); //gera o n�mero aleatorio

		//gerar aleatorio entre 0 e 1 se rand <= exp pegar se nao nao pegar (se der ruim troca)
		if (randNum < exp(delE / T))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	void SimulatedAnnealing::main(systemState problem) {


		double delE;
		int x = 1;
		double bestHeuristic = problem.get_heuristic();

		systemState current = problem; //define a corrente como estado inicial
		systemState next;
		systemState best;
		unsigned int count = 0;

		while (tempeture > 0)
		{
			try
			{
				next = RandomValue(current); //funcao que retorna um estado aleatorio 				
			}
			catch (const int error)
			{
				if (error == 1)
				{
					std::cout << "\nSem proximos movimentos\n";
					break;
				}
			}
			delE = next.get_heuristic() - current.get_heuristic();
			if (delE < 0.0)
			{
				current = next;
				/*if (current.get_heuristic() > bestHeuristic)
				{
					bestHeuristic = current.get_heuristic();
					best = current;
				}*/
				if (current.get_heuristic() == 0) //se for uma k-tupla adiciona na pilha de resposta
				{
					lopt.push(current.get_cklist());
				}
			}
			else if (RandomProbability(delE, tempeture))
			{
				current = next;
			}
			tempeture = tempeture - decay;
			no_of_visited_solutions++;
			std::cout << "\nheuristica: " << current.get_heuristic() << "-----TEMPERATURA: " << tempeture;
		}
	}

	void SimulatedAnnealing::report() {

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
