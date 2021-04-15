#include"./header/systemState.h"


	systemState::systemState() {};
	systemState::~systemState() {};
	systemState::systemState(std::vector<unsigned int> cklist, criticality& critical_data, std::string x) {
		CKLIST = cklist;
		CRITICAL_DATA = critical_data;
		DEEPTH = set_depth();
		TYPE_SEARCH = x;
		if (TYPE_SEARCH == "measurement")
		{
			HEURISTIC = measurement_heuristic();
		}
		else
		{
			HEURISTIC = munit_heuristic();
		}
		HEURISTIC = HEURISTIC;
	}

	bool systemState::evalueCK() {
		if (TYPE_SEARCH == "measurement")
		{
			return measurement_evalueCK();
		}
		else
		{
			return  munit_evalueCK();
		}
	}

	bool systemState::munit_evalueCK() { //determina se a tupla possui uma tupla critica dentro dela (avaliacao por medidor)
		if (HEURISTIC == 0)
		{
			for (size_t i = 0; i < CKLIST.size(); i++)
			{
				std::vector<unsigned int> newVector = CKLIST;

				if (newVector[i] == 1)
				{
					newVector[i] = 0;
					if (CRITICAL_DATA.munit_criticality(newVector) == 1)
					{
						return false;//tupla contem uma ktupla critica dentro dela
					}
				}
			}
		}
		return true;//tupla nao contem uma ktupla critica dentro dela
	}

	bool systemState::measurement_evalueCK() {//determina se a tupla possui uma tupla critica dentro dela (avaliacao por medida)
			for (size_t i = 0; i < CKLIST.size(); i++)
			{
				std::vector<unsigned int> newVector = CKLIST;
				if (newVector[i] == 1)
				{
					newVector[i] = 0;
					if (CRITICAL_DATA.measurement_criticality(newVector) == 1)
					{
						return false; //tupla contem uma ktupla critica dentro dela
					}
				}
			}
		return true; //tupla nao contem uma ktupla critica dentro dela
	}

	unsigned int systemState::set_depth() {
		unsigned int count = 0;
		for (size_t i = 0; i < CKLIST.size(); i++)
		{
			if (CKLIST[i] == 1)
			{
				count++;
			}
		}
		return  count;
		//return count;
	}
	double systemState::measurement_heuristic() {
		double heuristic;
		if (CRITICAL_DATA.measurement_criticality(CKLIST) == 1)
		{
			heuristic = 0;
		}
		else
		{
			heuristic = CRITICAL_DATA.get_det();
		}

		/*if (heuristic == 0)
		{
			if (measurement_evalueCK())
			{
				return heuristic;
			}
			else
			{
				return std::numeric_limits<double>::max();
			}
		}*/
		return heuristic;
	}
	double systemState::munit_heuristic() {

		CRITICAL_DATA.munit_criticality(CKLIST);
		return CRITICAL_DATA.get_det();
	}
