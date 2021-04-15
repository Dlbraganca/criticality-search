#include "./header/criticality.h"

criticality::criticality() {
	// default constructor
};

criticality::~criticality() {
	// default constructor
};

criticality::criticality(const char* H_FILE, const char* M_FILE, const char* A_FILE, const char* MU_FILE) {

	std::string line;
	unsigned int mu_bus;
	std::ifstream mu_file(MU_FILE, std::ios::in);
	//std::ofstream jac_file("jacob_cpp",std::ios::out);

	if (mu_file.is_open()) {
		std::cout << "mu_file open correctly" << std::endl;
	}
	std::cout << "Reading SE data ..." << std::endl;
	// read Measurement system configuration
	getline(mu_file, line, ' ');
	nm = std::stoul(line, nullptr, 10);
	getline(mu_file, line);
	mu_size = std::stoul(line, nullptr, 10); //transforma a linha lida em numero
	meas_location = std::vector<std::size_t>(nm, 0);
	while (getline(mu_file, line)) {// read mu location (bus)
		//unsigned int pos1 = 0, pos2 = 0;
		std::size_t pos1 = 0, pos2 = 0;
		std::string aux_str;
		pos2 = line.find(' ', pos1);
		if (pos2 != line.npos) { aux_str = line.substr(pos1, (pos2 - pos1)); }
		else { aux_str = line; }
		mu_bus = std::stoul(aux_str, nullptr, 10);
		mu_location.push_back(mu_bus - 1);
		//std::cout<<"\n"<<mu_location.back();
		while (pos2 != line.npos) { //read measurements collected by the MU
			pos1 = pos2 + 1;
			pos2 = line.find(' ', pos1);
			aux_str = line.substr(pos1, (pos2 - pos1));
			meas_location[std::stoul(aux_str, nullptr, 10) - 1] = mu_location.size() - 1;
			//std::cout<<" "<<std::stoul(aux_str, nullptr, 10)-1<<"("<<meas_location[std::stoul(aux_str, nullptr, 10)-1]<<")";
		}
	}
	//std::cout<<std::endl;
	mu_file.close();

	// read matlab matrices
	H = read_matlab_matrix("H.txt");
	M = read_matlab_matrix("M.txt");
	A = read_matlab_matrix("A.txt");
	ns = H.n_cols; // number of states

	std::cout << "number of measurements:   " << nm << std::endl;
	std::cout << "number of states:   " << ns << std::endl;
	std::cout << "number of measurement units:  " << mu_size << std::endl;
	//H.print("\nJacobian matrix - H :");
	//H.print(jac_file);
	//M.print("\nMeasurement to branch incidence matrix - M:");
	//A.print("\nBranch to node incidence matrix - A:");
	std::cout << "\nSE data sucsscessfully read !!!" << std::endl;
};

/*
criticality& criticality::operator=(const criticality& CRIT_OBJ) {
	// assign all member data
	meas_ck=CRIT_OBJ.meas_ck;
	branch_ck = CRIT_OBJ.branch_ck;
	mu_ck = CRIT_OBJ.mu_ck;
	H = CRIT_OBJ.H;
	M = CRIT_OBJ.M;
	A = CRIT_OBJ.A;
	G = CRIT_OBJ.G;
	E = CRIT_OBJ.E;
	H = CRIT_OBJ.H;
	nm = CRIT_OBJ.nm;
	ns = CRIT_OBJ.ns;
	mu_location = CRIT_OBJ.mu_location;
	meas_location = CRIT_OBJ.meas_location;

	return *this;
};
*/

/*
criticality::criticality(const criticality& CRIT_OBJ) {
	std::stack<std::vector<unsigned int>> meas_ck = CRIT_OBJ.meas_ck;
	std::stack<std::vector<unsigned int>> branch_ck = CRIT_OBJ.branch_ck;
	std::stack<std::vector<unsigned int>> mu_ck = CRIT_OBJ.mu_ck;
	H = CRIT_OBJ.H;
	M = CRIT_OBJ.M;
	A = CRIT_OBJ.A;
	G = CRIT_OBJ.G;
	E = CRIT_OBJ.E;
	H = CRIT_OBJ.H;
	std::size_t nm = CRIT_OBJ.nm;
	std::size_t ns = CRIT_OBJ.ns;
};
*/

arma::mat criticality::read_matlab_matrix(const char* MATRIX_FILENAME) {
	std::string line;
	std::ifstream matrix_file;
	double* A_vec = nullptr;
	unsigned int i, j, nrows, ncols; //k,
	arma::mat A;

	matrix_file.open(MATRIX_FILENAME, std::ios_base::in);
	if (matrix_file.is_open()) {
		std::getline(matrix_file, line);
		nrows = std::stoul(line, nullptr, 10);
		std::getline(matrix_file, line);
		ncols = std::stoul(line, nullptr, 10);
		A_vec = new double[nrows * ncols];
		if (nrows == 1 && ncols == 1) {
			std::getline(matrix_file, line);
			ncols = std::stoul(line, nullptr, 10);
			A_vec[0] = std::stod(line, nullptr);
		}
		else {
			std::getline(matrix_file, line);
			std::size_t pos1, pos2;
			/*
			pos1 = line.find('[');
			line.erase(line.begin() + pos1);
			pos1 = line.find(']');
			line.erase(line.begin() + pos1);
			*/
			// read vectorized (Column major order) matrix 
			pos1 = 0;
			pos2 = line.find(' ');
			i = 0;
			while (pos2 != line.npos) {
				A_vec[i] = std::stod(line.substr(pos1, (pos2 - pos1)));
				pos1 = pos2 + 1;
				pos2 = line.find(' ', pos1);
				i++;
			}
			if (pos2 == line.npos && pos1 < line.size()) {
				A_vec[i] = std::stod(line.substr(pos1));
			}
		}
		/*
				std::cout << "Nrows:   " << nrows << "    Ncols:   " << ncols << std::endl;
				for (i = 0; i < nrows*ncols; i++) {
					std::cout << A_vec[i] << " ";
				}
		*/
		A.resize(nrows, ncols);
		for (j = 0; j < ncols; j++) // transform vectorized matrix into rectangle form
			for (i = 0; i < nrows; i++) {
				A(i, j) = A_vec[nrows * j + i];
			}
		/*		std::cout << "\n Digite algo para terminar" << std::endl;
				std::cout << j + 1 << std::endl;
		*/
		matrix_file.close();
		//A.print("A:");
		delete[] A_vec;
	}
	else { std::cout << "Unable to open the file" << std::endl; }
	return A;
};

unsigned int  criticality::eval_criticality(std::vector<unsigned int>& x, std::string& CRIT_TYPE) {
	unsigned int f;
	if (CRIT_TYPE.compare("measurement") == 0) {
		f = measurement_criticality(x);
	}
	if (CRIT_TYPE.compare("munit") == 0) {
		//objfuncPtr = &criticalities::munit_criticality;
		f = munit_criticality(x);
	}
	if (CRIT_TYPE.compare("complete_munit") == 0) {
		//objfuncPtr = &criticalities::munit_criticality;
		f = complete_munit_criticality(x);
	}
	if (CRIT_TYPE.compare("top") == 0) {
		f = top_branch_criticality((x));
	}
	if (CRIT_TYPE.compare("bd_top") == 0) {
		f = bd_branch_criticality(x);
	}
	return f;
}

unsigned int  criticality::measurement_criticality(std::vector<unsigned int> x)
{
	unsigned int nrows, ncolumns = H.n_cols, row, row2, col;
	arma::mat H2, G2, Q;
	arma::vec d;
	arma::uvec non_zeros;
	// determining the number of rows
	nrows = 0;
	for (std::vector<unsigned int>::iterator it = x.begin(); it != x.end(); ++it) {
		if (*it == 0) {
			++nrows;
		}
	}
	H2.resize(nrows, ncolumns); //resize H2
								// create H2 from H selected rows
	row = 0;
	row2 = 0;
	//std::cout << "Removed rows:" << std::endl;
	for (row = 0; row < H.n_rows; row++) {
		if (x[row] == 0) { // do not remove row			
			for (col = 0; col < ncolumns; col++) {
				H2(row2, col) = H(row, col);
			}
			row2++;
		}
		//else {
		//std::cout << "    " << (row + 1);
		//}
	}
	//std::cout << "\n";
	/*std::cout << "matrix H:" << std::endl;
	H.print();
	std::cout << "matrix H2:" << std::endl;
	H2.print();
	std::cout << "###################################" << std::endl;*/
	return observability_analysis(H2);
}

unsigned int  criticality::top_branch_criticality(std::vector<unsigned int>& x)
{
	return 0;
}

unsigned int  criticality::munit_criticality(std::vector<unsigned int> x) {

	unsigned int nrows = 0, ncolumns = H.n_cols, row, row2, col;
	arma::mat H2, G2, Q;
	arma::vec d;
	arma::uvec non_zeros;
	std::vector<unsigned int> y(H.n_rows, 0); //vector of available measurements

	//std::cout<<"\nmeas_locatio_size:"<<meas_location.size()<<"\nmeas_size:"<<H.n_rows<<std::endl;

	for (unsigned int j = 0; j < meas_location.size(); j++) {
		if (x[meas_location[j]] == 1) { // if the associated MU is unavailable, then make the measurement unavailable too
			y[j] = 1; //std::cout<<j<<" ";
		}
		else { nrows++; }
	}
	//std::cout<<"\n";
/*
	for (unsigned int i = 0; i < x.size(); i++) {
		for (unsigned int j = 0; j < meas_location.size(); j++) {
			if (i==meas_location[j]) { // set all elements associated to the meas unit as unavailable
				y[j] = 1;
			}
			else { nrows++; }
		}
	}
*/
	H2.resize(nrows, ncolumns); //resize H2 and create H2 from selected rows (thos such that y[row]=0) of H								
	row = 0;
	row2 = 0;
	for (row = 0; row < H.n_rows; row++) {
		if (y[row] == 0) { // do not remove row			
			for (col = 0; col < ncolumns; col++) {
				H2(row2, col) = H(row, col);
			}
			row2++;
		}
	}
	/*std::cout << "matrix H:" << std::endl;
	H.print();
	std::cout << "matrix H2:" << std::endl;
	H2.print();
	std::cout << "###################################" << std::endl;*/
	return observability_analysis(H2);
}

unsigned int  criticality::complete_munit_criticality(std::vector<unsigned int>& x)
{

	std::vector<unsigned int> y(A.n_cols, 1); //everyone is unavailable 
	for (unsigned int i = 0; i < x.size(); i++) {
		if (x[i] == 0) { // The ith installed mu is avaliable
			y[mu_location[i]] = 0;
		}
	}
	return munit_observability_analysis(y, A);

}

unsigned int  criticality::bd_branch_criticality(std::vector<unsigned int>& x)
{
	return 0;
}

unsigned int criticality::observability_analysis(arma::mat H, double tol) {
	arma::mat  G, Q;
	//arma::mat  G, L, D, A;
	arma::vec d;
	arma::uvec non_zeros;

	//std::ofstream gain_cpp("G_hist.txt",std::ios::out | std::ios::app);
	// compute gain matrix
	G = H.t() * H;
	//gain_cpp<<H<<std::endl;
	//gain_cpp<<G<<std::endl;
	arma::qr_econ(Q, U, G); // QR decomposition of G2
	d = arma::diagvec(U); // extracts main diagonal of triangular matrix U
	//d.t().print(gain_cpp,"d:");gain_cpp<<arma::rank(G)<<arma::cond(G)<<std::endl;
	//det = arma::det(U);
	non_zeros = arma::find(arma::abs(d) > tol);
	if (non_zeros.size() < H.n_cols) {  //if the number of non zero pivots in U is lesser than number of states, system is unobservable
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned int  criticality::munit_observability_analysis(std::vector<unsigned int> y, arma::mat A) {
	/*
		struct island {
			std::vector<std::size_t> buses;
			island() { 		}
		};

		std::size_t N = y.size();
		unsigned int island_count = 0;
		std::vector<island> observable_island_vec;
		std::vector<std::size_t>::iterator it;

		for (std::size_t i = 0; i < N; i++) { // initialize bus islands (one bus per island)
			observable_island_vec.push_back(island());
			observable_island_vec[i].buses.push_back(i + 1);
		}
		for (std::size_t i = 0; i < N; i++) {
			if (y[i] == 0) { //Measurement unit i is available
				for (unsigned  j = 0; j<A.n_rows; j++) {
					if (abs(A(j, i)) != 0) { //Measurement unit i is incident to branch j
						for (unsigned  k = 0; k<A.n_cols; k++) {
							if (abs(A(j, k)) != 0 && k != i) {
								if (observable_island_vec[k].buses.size() != 0) {
									it = observable_island_vec[i].buses.end();
									observable_island_vec[i].buses.insert(it, observable_island_vec[k].buses.begin(), observable_island_vec[k].buses.end());
									observable_island_vec[k].buses.clear();
								}
								else {
									bool find = false;
									for (unsigned  l = 0; l<observable_island_vec.size(); l++) {
										for (unsigned  m = 0; m<observable_island_vec[l].buses.size(); m++) {
											if (k == observable_island_vec[l].buses[m] && l != i) {
												find = true;
												it = observable_island_vec[i].buses.end();
												observable_island_vec[i].buses.insert(it, observable_island_vec[l].buses.begin(), observable_island_vec[l].buses.end());								observable_island_vec[k].buses.clear();
												observable_island_vec[l].buses.clear();
												break; //break m loop
											}
										}
										if (find) { break; } //break l loop
									}
								}
								break; // break k loop
							}
						}
					}
				}
			}
		}
		for (unsigned int i = 0; i < observable_island_vec.size(); i++) {
			if (observable_island_vec[i].buses.size() != 0) {
				island_count++;
			}
		}
		if (island_count == 1) { return 0; }
		else { return 1; }
	*/
	return 0;
}
//void printa_matriz(std::vector<std::vector<unsigned int>>x) {
//	for (size_t i = 0; i < x.size(); i++)
//	{
//		for (size_t j = 0; j < x[i].size(); j++)
//		{
//			std::cout << x[i][j] << " ";
//		}
//		std::cout << "\n";
//	}
//}
