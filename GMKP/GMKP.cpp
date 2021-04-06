#include <iostream> // input/output
#include <fstream> // read files
#include <sstream>
#include <stdlib.h>

#include <sstream>
#include <string>
#include <time.h>

#include <random>
#include "pugixml.hpp"

#include "GMKP_CPX.h"
#include "GMKP_CONCERT.h"

using namespace std;

void addItemInClass(int r, int n, int class_gen, int item, int * indexes, int * classes);

int main(int argc, char **argv) {

	// data for GMKP instance
	int n; // number of objects
	int m; // number of knapsacks
	int r; // number of subsets
	int *profits; // array for linear profit term
	int *weights; // array of weights
	int *capacities; // array of knapsack capacities
	int *setups; // array of setup
	int *classes; // array of classes
	int *indexes; // array of indexes

	clock_t start, end;
	double time;

	// output data
	int status = 0;

	// read configuration
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("config.xml");
	if (result) {
		std::cout << "config.xml loaded correctly!\n";
	}
	else {
		std::cout << "config.xml not found or not written correctly!\n";
		return -1;
	}

	std::cout << "Parameters" << std::endl;

	// library
	std::string library = doc.child("Config").child("library").attribute("name").as_string();
	std::cout << "library used: " << library << std::endl;

	// timeout
	int TL = doc.child("Config").child("timeout").attribute("value").as_int();
	std::cout << "timeout: " << TL << "s" << std::endl;

	// number of instance
	int n_instances = doc.child("Config").child("instances").attribute("number").as_int();
	std::cout << "number of instances to create: " << n_instances << std::endl;

	// number of items
	n = doc.child("Config").child("items").attribute("number").as_int();
	weights = (int *)malloc(sizeof(int) * n);
	std::cout << "items:" << n << std::endl;

	// number of knapsacks
	m = doc.child("Config").child("knapsacks").attribute("number").as_int();
	capacities = (int *)malloc(sizeof(int) * m);
	profits = (int *)malloc(sizeof(int) * n * m);
	std::cout << "knapsacks: " << m << std::endl;

	// number of classes
	r = n / 5;

	setups = (int *)malloc(sizeof(int) * r);
	classes = (int *)malloc(sizeof(int) * n);
	indexes = (int *)malloc(sizeof(int) * r);
	std::cout << "classes:" << r << std::endl;

	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());

	// generate istance
	for (int inst = 0; inst < n_instances; inst++) {
		// create istance file
		char istanceFilename[200];
		strcpy(istanceFilename, "instances/randomGMKP_");
		std::stringstream strs;
		strs << inst + 1 << ".inc";
		std::string temp_str = strs.str();
		const char* char_type = (char*)temp_str.c_str();
		strcat(istanceFilename, char_type);

		std::ofstream output;
		output.open(istanceFilename);

		output << "sets" << std::endl;

		// number of items
		output << "\tj items\t" << n << std::endl;

		// number of knapsacks
		output << "\tk knapsacks\t" << m << std::endl;

		// number of classes
		output << "\tr classes\t" << r << std::endl;

		output << "parameter w(j)" << std::endl;
		int sum_weights = 0;
		std::uniform_int_distribution<int> w_distr(10, 100);
		for (int i = 0; i < n; i++) {

			// generate weights
			weights[i] = w_distr(generator);
			output << i + 1 << "\t" << weights[i] << "\n";

			sum_weights += weights[i];

		}

		output << std::endl;

		output << "parameter cap(k)" << std::endl;
		// generate capacities
		double capacities_i = 0;
		for (int i = 1; i < m; i++) {
			std::uniform_real_distribution<double> c_distr(0, 0.5*sum_weights - capacities_i);

			capacities_i += c_distr(generator);
		}

		for (int i = 0; i < m; i++) {
			capacities[i] = (int)((0.5 * sum_weights) - capacities_i);
		}
		output << "cap(k)=" << capacities[0] << std::endl;

		output << std::endl;

		output << "parameter p(i, j)" << std::endl;
		for (int i = 0; i < n*m; i++) {

			// generate profits
			std::uniform_int_distribution<int> p_distr(10, 100);
			profits[i] = p_distr(generator);

			output << i + 1 << "\t" << profits[i] << std::endl;
		}

		output << std::endl;

		output << "parameter t(r,j)" << std::endl;
		std::uniform_int_distribution<int> trj_distr(1, r);
		for (int i = 0; i < n; i++) {

			if (i < r) {
				classes[i] = i;
				indexes[i] = i + 1;
				output << i + 1 << "." << i + 1 << "=1" << std::endl;
			}
			else {

				int class_gen = trj_distr(generator);
				addItemInClass(r, n, class_gen, i, indexes, classes);
				output << class_gen << "." << i + 1 << "=1" << std::endl;

			}

		}

		output << std::endl;

		output << "parameter s(r)" << std::endl;
		for (int i = 0; i < r; i++) {

			std::uniform_int_distribution<int> s_distr(50, 100);
			setups[i] = s_distr(generator);
			output << i + 1 << "\t" << setups[i] << std::endl;
		}

		// close istance file
		output.close();

		std::cout << "\nStart to create CPLEX problem number " << inst + 1 << std::endl;

		// model into a .lp file
		char modelFilename[200];
		strcpy(modelFilename, "models/model_");
		std::stringstream strs2;
		strs2 << inst + 1 << ".lp";
		temp_str = strs2.str();
		char_type = (char*)temp_str.c_str();
		strcat(modelFilename, char_type);

		// log into a .txt file
		char logFilename[200];
		strcpy(logFilename, "logs/log_");
		std::stringstream strs3;
		strs3 << inst + 1 << ".txt";
		temp_str = strs3.str();
		char_type = (char*)temp_str.c_str();
		strcat(logFilename, char_type);

		// solve problem
		if (library._Equal("callable library"))
			status = solveGMKP_CPX(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, false);
		else
			status = solveGMKP_CONCERT(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, false);

		// print output
		if (status)
			std::cout << "An error has occurred! Error number : " << status << std::endl;
		else
			std::cout << "The function was performed correctly!" << std::endl;

		//std::cout << std::endl;
		//status = solveGMKP_CONCERT(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, false);

		std::cout << std::endl;

		start = clock();
		// solve problem
		if (library._Equal("callable library"))
			status = solveGMKP_CPX(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, true);
		else
			status = solveGMKP_CONCERT(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, true);
		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC;

		// print output
		if (status) {
			std::cout << "An error has occurred! Error number : " << status << std::endl;
		}
		else {
			std::cout << "The function was performed correctly!" << std::endl;
			std::cout << "Elapsed time: " << time << std::endl;
		}

		//std::cout << std::endl;
		//status = solveGMKP_CONCERT(n, m, r, weights, profits, capacities, setups, classes, indexes, modelFilename, logFilename, TL, true);


	} // istances

	// free memory
	free(profits);
	free(weights);
	free(capacities);
	free(setups);
	free(classes);
	free(indexes);
	
	return 0;
}

void addItemInClass(int r, int n, int class_gen, int item, int * indexes, int * classes) {

	for (int i = 0; i < r; i++) {

		// find the class
		if (i + 1 == class_gen) {
			// move an element forward 
			for (int j = n - 1; j > indexes[i]; j--) {
				classes[j] = classes[j - 1];
			}

			classes[indexes[i]] = item;

			// update indexes
			for (int j = i; j < r; j++) {
				indexes[j] += 1;
			}
		}

	} // for r

}