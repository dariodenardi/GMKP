#include "OPL_CONV.h"

int convertLpToMod(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modFilename) {

	std::ofstream outfile(modFilename);

	auto time = std::time(nullptr);
	std::cout.imbue(std::locale("en_US.utf8"));

	outfile << "/*********************************************" << std::endl;
	outfile << " * OPL 12.9.0.0 Model" << std::endl;
	outfile << " * Generated Automatic" << std::endl;
	outfile << " * Creation Date: " << std::put_time(std::gmtime(&time), "%d %B %Y") << " at " << std::put_time(std::gmtime(&time), "%T") << std::endl;
	outfile << " *********************************************/" << std::endl;
	outfile << std::endl;

	// write variables x
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			outfile << "dvar boolean x_" << i + 1 << "_" << j + 1 << ";" << std::endl;
		}
	}

	// write variables y
	for (int i = 0; i < m; i++) {
		for (int k = 0; k < r; k++) {

			outfile << "dvar boolean y_" << i + 1 << "_" << k + 1 << ";" << std::endl;
		}
	}

	outfile << std::endl;
	outfile << "maximize ";

	// write profits
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			outfile << profits[i*n + j] << "*x_" << i + 1 << "_" << j + 1;

			if (j != n - 1)
				outfile << " + ";
		}

		if (i != m - 1)
			outfile << " + ";
	}

	outfile << ";" << std::endl << std::endl;
	outfile << "subject to {" << std::endl << std::endl;
	
	// write constraint 1
	for (int i = 0; i < m; i++) {
		// write profits
		for (int j = 0; j < n; j++) {

			outfile << weights[j] << "*x_" << i + 1 << "_" << j + 1;

			outfile << " + ";
		}

		// write setups
		for (int k = 0; k < r; k++) {

			outfile << setups[k] << "*y_" << i + 1 << "_" << k + 1;

			if (k != r - 1)
				outfile << " + ";
		}

		outfile << " <= " << capacities[i] << ";" << std::endl << std::endl;
	}

	// write constraint 2
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {

			outfile << "x_" << i + 1 << "_" << j + 1;

			if (i != m - 1)
				outfile << " + ";
		}

		outfile << " <= 1;" << std::endl << std::endl;
	}

	// write constraint 3
	for (int k = 0; k < r; k++) {
		for (int i = 0; i < m; i++) {

			outfile << "y_" << i + 1 << "_" << k + 1;

			if (i != m - 1)
				outfile << " + ";
		}

		outfile << " <= " << b[k] << ";" << std::endl << std::endl;
	}

	// write constraint 4
	for (int i = 0; i < m; i++) {
		for (int k = 0; k < r; k++) {

			for (int j = 0; j < n; j++) {

				int indexes_prev = k > 0 ? indexes[k - 1] : 0;
				for (int z = 0; z < indexes[k] - indexes_prev; z++) {

					if (classes[z + indexes_prev] == j) {
						outfile << "x_" << i + 1 << "_" << j + 1;

						if (z + 1 < indexes[k] - indexes_prev)
							outfile << " + ";
					}
				}

			} // j (items)

			outfile << " - " << n << "*y_" << i + 1 << "_" << k + 1 << " <= 0;";
			outfile << std::endl << std::endl;

		} // k (classes)

	} // i (knapsacks)

	outfile << "}";

	outfile.close();

	return 0;
}