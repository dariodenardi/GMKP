// GMKP.cpp : this file contains the function 'main', which starts and finishes the execute of the program.
//

#include <iostream> // input/output
#include <fstream> // read files

#include "GMKP_CPX.h"

int main() {
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

	// read instance
	n = 6;
	profits = (int *)malloc(sizeof(int)*n);
	weights = (int *)malloc(sizeof(int)*n);
	std::cout << "number of objects: " << n << "\n";

	profits[0] = 100;
	profits[1] = 49;
	profits[2] = 36;
	profits[3] = 15;
	profits[4] = 18;
	profits[5] = 15;

	weights[0] = 15;
	weights[1] = 10;
	weights[2] = 9;
	weights[3] = 4;
	weights[4] = 5;
	weights[5] = 5;

	m = 2;
	capacities = (int *)malloc(sizeof(int)*m);
	std::cout << "number of knapsacks: " << m << "\n";

	capacities[0] = 30;
	capacities[1] = 12;

	r = 2;
	setups = (int *)malloc(sizeof(int)*r);
	classes = (int *)malloc(sizeof(int)*n);
	indexes = (int *)malloc(sizeof(int)*r);
	std::cout << "numer of classes: " << r << "\n";

	setups[0] = 1;
	setups[1] = 2;

	classes[0] = 0;
	classes[1] = 1;
	classes[2] = 3;
	classes[3] = 5;
	classes[4] = 2;
	classes[5] = 4;

	indexes[0] = 4;
	indexes[1] = 6;

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
	IloRangeArray big_m(env);

	solveGMKP_CPX(model, obj, capacity, max_one_bin, big_m, x, y, n, m, r, weights, profits, capacities, setups, classes, indexes);

	// add all to the model
	model.add(obj);
	model.add(capacity);
	model.add(max_one_bin);
	model.add(big_m);

	IloCplex cplex(model);

	// export the model into an .lp file
	cplex.exportModel("model.lp");

	// solve the problem
	if (cplex.solve()) {
		std::cout << "CPLEX model solved! (Status: " << cplex.getStatus() << ")" << std::endl;
		std::cout << "The objective value is: " << cplex.getObjValue() << std::endl;
	}
	else {
		std::cerr << "CPLEX failed! (Status: " << cplex.getStatus() << ", " << cplex.getCplexStatus() << ")" << std::endl;
	}

	// clean up memory
	env.end();

	// free memory
	free(profits);
	free(weights);
	free(capacities);
	free(setups);
	free(classes);
	free(indexes);

	return 0;
}