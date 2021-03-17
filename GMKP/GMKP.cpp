// GMKP.cpp : this file contains the function 'main', which starts and finishes the execute of the program.
//

#include <iostream> // input/output
#include <fstream> // read files

#include <sstream>
#include <string>

#include <random>
#include "pugixml.hpp"

#include "GMKP_CPX.h"

void addItemInClass(int r, int n, int class_gen, int item, int * indexes, int * classes);

int main() {
	// data for GMKP instance
	int n; // number of objects
	int m; // number of knapsacks
	int r; // number of subsets
	int *profits; // array of profits
	int *weights; // array of weights
	int *capacities; // array of knapsacks capacities
	int *setups; // array of setups
	int *classes; // array of classes
	int *indexes; // array of indexes

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

	// timeout
	int timeout = doc.child("Config").child("timeout").attribute("value").as_int();
	std::cout << "timeout: " << timeout << std::endl;

	// number of instance
	int n_instances = doc.child("Config").child("instances").attribute("number").as_int();
	std::cout << "number of instances to create: " << n_instances << std::endl;

	// number of items
	n = doc.child("Config").child("items").attribute("number").as_int();
	profits = (int *)malloc(sizeof(int) * n);
	weights = (int *)malloc(sizeof(int) * n);
	std::cout << "items:" << n << std::endl;

	// level
	int level = doc.child("Config").child("level").attribute("group").as_int();
	std::cout << "level: " << level << std::endl;

	int w_marked;
	int p_marked;
	if (level == 1) {
		w_marked = 10;
		p_marked = 100;
	}
	else if (level == 2) {
		w_marked = 20;
		p_marked = 200;
	}
	else if (level == 3) {
		w_marked = 30;
		p_marked = 300;
	}
	else if (level == 4) {
		w_marked = 40;
		p_marked = 400;
	}
	else if (level == 5) {
		w_marked = 50;
		p_marked = 500;
	}

	// correlation
	std::string correlation = doc.child("Config").child("correlation").attribute("type").as_string();
	std::cout << "correlation: " << correlation << std::endl;

	// number of knapsacks
	m = doc.child("Config").child("knapsacks").attribute("number").as_int();
	capacities = (int *)malloc(sizeof(int) * m);
	std::cout << "knapsacks: " << m << std::endl;

	// c ratio
	double c_ratio = doc.child("Config").child("c_ratio").attribute("ratio").as_double();
	std::cout << "c-ratio: " << c_ratio << std::endl;

	// item distribution
	std::string trj = doc.child("Config").child("item_distribution").attribute("type").as_string();
	std::cout << "t(r, j): " << trj << std::endl;

	// setups
	std::string s_config = doc.child("Config").child("setups").attribute("type").as_string();
	std::cout << "s(r): " << s_config << std::endl;

	// number of classes
	std::string r_config = doc.child("Config").child("classes").attribute("type").as_string();
	if (r_config._Equal("low")) {
		r = n / 10;
	}
	else if (r_config._Equal("high")) {
		r = n / 2;
	}

	// density
	double density = doc.child("Config").child("density").attribute("ratio").as_double();
	std::cout << "density: " << density << std::endl;

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
		std::uniform_int_distribution<int>  w_distr(1, w_marked);
		for (int i = 0; i < n; i++) {

			// generate weights
			weights[i] = w_distr(generator);
			output << i + 1 << "\t" << weights[i] << "\n";

			sum_weights += weights[i];

		}

		output << std::endl;

		output << "parameter cap(k)" << std::endl;
		// generate capacities
		for (int i = 0; i < m; i++) {
			capacities[i] = (int)(c_ratio * sum_weights / m);
		}
		output << "cap(k)=" << capacities[0] << std::endl;

		output << std::endl;

		output << "parameter p(j)" << std::endl;
		std::uniform_real_distribution<double> d_distr(0, 1);
		for (int i = 0; i < n; i++) {

			double density_random = d_distr(generator);

			// generate profits
			if (correlation._Equal("nothing")) {
				std::uniform_int_distribution<int> p_distr(0, p_marked);

				if (density_random >= density) {
					profits[i] = 0;
				}
				else {
					profits[i] = p_distr(generator);
				}
			}
			else if (correlation._Equal("weakly")) {
				std::uniform_int_distribution<int> p_distr(0, p_marked / 10);

				if (density_random >= density) {
					profits[i] = 0;
				}
				else {
					profits[i] = 10 * weights[i] + p_distr(generator);
				}
			}
			else if (correlation._Equal("strongly")) {

				if (density_random >= density) {
					profits[i] = 0;
				}
				else {
					profits[i] = 10 * weights[i] + p_marked / 10;
				}
			}
			output << i + 1 << "\t" << profits[i] << std::endl;

		}

		output << std::endl;

		output << "parameter t(r,j)" << std::endl;
		std::uniform_int_distribution<int> trj_distr(1, r);
		int one_class_dense = trj_distr(generator);
		for (int i = 0; i < n; i++) {

			if (i < r) {
				classes[i] = i;
				indexes[i] = i + 1;
				output << i + 1 << "." << i + 1 << "=1" << std::endl;
			}
			else {

				if (trj._Equal("random")) {
					int class_gen = trj_distr(generator);
					addItemInClass(r, n, class_gen, i, indexes, classes);
					output << class_gen << "." << i + 1 << "=1" << std::endl;
				}
				else if (trj._Equal("one_class_dense")) {
					addItemInClass(r, n, one_class_dense, i, indexes, classes);
					output << one_class_dense << "." << i + 1 << "=1" << std::endl;
				}

			}

		}

		output << std::endl;

		output << "parameter s(r)" << std::endl;
		for (int i = 0; i < r; i++) {

			if (s_config._Equal("low")) {
				std::uniform_int_distribution<int> s_distr(1, w_marked / 4);
				setups[i] = s_distr(generator);
			}
			else if (s_config._Equal("high")) {
				std::uniform_int_distribution<int> s_distr(w_marked / 4, w_marked / 2);
				setups[i] = s_distr(generator);
			}
			output << i + 1 << "\t" << setups[i] << std::endl;

		}

		// close istance file
		output.close();

		std::cout << "\nStart to create CPLEX problem number " << inst + 1 << std::endl;

		IloEnv env;
		IloModel model(env);

		// set problem name
		model.setName("Generalized Multiple Knapsack Problem");

		// variables (columns)
		IloNumVarArray x(env);
		IloNumVarArray y(env);

		// objective function
		IloObjective obj = IloMaximize(env);

		// constraints (rows)
		IloRangeArray capacity(env);
		IloRangeArray max_one_bin(env);
		IloRangeArray dependent_decision(env);

		// solve problem
		solveGMKP_CPX(model, obj, capacity, max_one_bin, dependent_decision, x, y, n, m, r, weights, profits, capacities, setups, classes, indexes);

		// add all to the model
		model.add(obj);
		model.add(capacity);
		model.add(max_one_bin);
		model.add(dependent_decision);

		IloCplex cplex(model);

		// set timeout
		cplex.setParam(IloCplex::Param::TimeLimit, timeout);

		// export the model into an .lp file
		char modelFilename[200];
		strcpy(modelFilename, "models/model_");
		std::stringstream strs2;
		strs2 << inst + 1 << ".lp";
		temp_str = strs2.str();
		char_type = (char*)temp_str.c_str();
		strcat(modelFilename, char_type);

		cplex.exportModel(modelFilename);

		// write log
		char logFilename[200];
		strcpy(logFilename, "logs/log_");
		std::stringstream strs3;
		strs3 << inst + 1 << ".txt";
		temp_str = strs3.str();
		char_type = (char*)temp_str.c_str();
		strcat(logFilename, char_type);

		std::ofstream log;
		log.open(logFilename);

		cplex.setOut(log);

		// solve the problem
		if (cplex.solve()) {
			std::cout << "CPLEX model solved! (Status: " << cplex.getStatus() << ")" << std::endl;
			std::cout << "The objective value is: " << cplex.getObjValue() << std::endl;
		}
		else {
			std::cerr << "CPLEX failed! (Status: " << cplex.getStatus() << ", " << cplex.getCplexStatus() << ")" << std::endl;
		}

		// close log file
		log.close();

		// clean up memory
		env.end();

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

		// cerco la classe
		if (i + 1 == class_gen) {
			// sposto di uno gli elementi in avanti
			for (int j = n - 1; j > indexes[i]; j--) {
				classes[j] = classes[j - 1];
			}

			classes[indexes[i]] = item;

			// aggiorno indici
			for (int j = i; j < r; j++) {
				indexes[j] += 1;
			}
		}

	} // for r

}