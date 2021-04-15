#include  "./header/ck_search.h"

ck_search::ck_search(){
	// default constructor
};

ck_search::ck_search(unsigned int KLIM, unsigned int KMIN, unsigned int KMAX, unsigned int DIM, std::string CRIT_TYPE, criticality& CRITICAL_DATA){
	// default constructor
	klim=KLIM;
	kmin=KMIN;
	kmax=KMAX;
	dim=DIM;
	crit_type=CRIT_TYPE;
	critical_data = CRITICAL_DATA;
};

ck_search::ck_search(const char* CK_PARAM_FILE, criticality& CRITICAL_DATA) {
	// default constructor
	read_problem_parameters(CK_PARAM_FILE);
	critical_data = CRITICAL_DATA;
};

ck_search::ck_search(const char* CK_PARAM_FILE) {
	// default constructor
	read_problem_parameters(CK_PARAM_FILE);
	critical_data=criticality("H.txt","M.txt","A.txt","MU.txt");
};

ck_search::~ck_search(){
// default destructor
};

void ck_search::read_problem_parameters(const char* CK_PARAM_FILENAME) {
	std::ifstream param_file(CK_PARAM_FILENAME, std::ios_base::in);
	std::string line;
	std::cout << "Reading search parameters ...";
	if (param_file.is_open()) {
		getline(param_file, line);
		search_method = line;
		getline(param_file, line);
		klim = std::stoul(line, nullptr, 10);
		getline(param_file, line);
		kmin = std::stoul(line, nullptr, 10);
		getline(param_file, line);
		kmax = std::stoul(line, nullptr, 10);
		getline(param_file, line);
		dim = std::stoul(line, nullptr, 10);
		getline(param_file, line);
		crit_type = line;
		param_file.close();
		std::cout << "done!!!" << std::endl;
	}	
	else {	std::cout << "Unable to open the file"<< std::endl;	}
}