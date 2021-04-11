#include "GMKP_CONCERT.h"

void add_rows(IloModel model, IloRangeArray capacity, IloRangeArray max_one_bin_x, IloRangeArray max_b_bin_y, IloRangeArray dependent_decision, IloNumVarArray y, int m, int n, int r, int * b, int * capacities, bool intflag);
void add_columns(IloModel model, IloObjective obj, IloRangeArray capacity, IloRangeArray max_one_bin_x, IloRangeArray max_b_bin_y, IloRangeArray dependent_decision, IloNumVarArray x, IloNumVarArray y, int n, int m, int r, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, bool intflag);

int solveGMKP_CONCERT(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modelFilename, char * logFilename, int TL, bool intflag) {

	IloEnv env;
	IloModel model(env);

	int status;

	// set problem name
	model.setName("GMKP - Concert Technologies");

	// variables (columns)
	IloNumVarArray x(env);
	IloNumVarArray y(env);

	// objective function
	IloObjective obj = IloMaximize(env);

	// constraints (rows)
	IloRangeArray capacity(env);
	IloRangeArray max_one_bin_x(env);
	IloRangeArray max_b_bin_y(env);
	IloRangeArray dependent_decision(env);

	add_rows(model, capacity, max_one_bin_x, max_b_bin_y, dependent_decision, y, m, n, r, b, capacities, intflag);
	add_columns(model, obj, capacity, max_one_bin_x, max_b_bin_y, dependent_decision, x, y, n, m, r, weights, profits, capacities, setups, classes, indexes, intflag);

	// add all to the model
	model.add(obj);
	model.add(capacity);
	model.add(max_one_bin_x);
	model.add(max_b_bin_y);
	model.add(dependent_decision);

	IloCplex cplex(model);

	// set timeout
	cplex.setParam(IloCplex::Param::TimeLimit, TL);

	// export the model into an .lp file
	cplex.exportModel(modelFilename);

	// write log
	std::ofstream log;
	log.open(logFilename);

	cplex.setOut(log);
	
	// solve the problem
	if (cplex.solve()) {
		if (intflag == false)
			std::cout << "Root UB: " << cplex.getObjValue() << std::endl;
		std::cout << "best UB: " << cplex.getBestObjValue() << std::endl;
		if (intflag == true)
			std::cout << "cut off: " << cplex.getObjValue() << std::endl;
		std::cout << "opt: " << cplex.getStatus() << std::endl;
		status = 0;
	}
	else
		status = cplex.getStatus();

	// check constraints
	if (intflag) {

		double *vectorX;
		vectorX = new double[n*m + m * r];
		for (IloInt i = 0; i < n*m; i++)
			vectorX[i] = cplex.getValue(x[i]);
		for (IloInt i = 0; i < r*m; i++)
			vectorX[n*m + i] = cplex.getValue(y[i]);

		int statusCheck = checkSolution(vectorX, cplex.getObjValue(), n, m, r, b, weights, profits, capacities, setups, classes, indexes);

		if (statusCheck == 0) {
			std::cout << "All constraints are ok" << std::endl;
		}
		else if (statusCheck == 1) {
			std::cout << "Constraint violated: weights of the items are greater than the capacity..." << std::endl;
		}
		else if (statusCheck == 2) {
			std::cout << "Constraint violated: item is assigned to more than one knapsack..." << std::endl;
		}
		else if (statusCheck == 3) {
			std::cout << "Constraint violated: class is assigned to more than one knapsack..." << std::endl;
		}
		else if (statusCheck == 4) {
			std::cout << "Constraint violated: items of class are not assigned to knapsack..." << std::endl;
		}
		else if (statusCheck == 5) {
			std::cout << "Optimal solution violeted..." << std::endl;
		}

		delete[] vectorX;
	}

	// close log file
	log.close();

	// clean up memory
	env.end();

	return status;
}

void add_rows(IloModel model, IloRangeArray capacity, IloRangeArray max_one_bin_x, IloRangeArray max_b_bin_y, IloRangeArray dependent_decision, IloNumVarArray y, int m, int n, int r, int * b, int * capacities, bool intflag) {
	IloEnv env = model.getEnv();
	std::stringstream name;

	for (int i = 0; i < m; i++) {
		// add constraint (1):
		// sum(j = 1 ... n) w_j * x_ij + sum(k = 1 ... r) s_k * y_ik <= C_i   for all i = 1 .. m
		name.str(std::string());
		name << "capacity_" << i + 1;
		capacity.add(IloRange(env, -IloInfinity, capacities[i], name.str().c_str())); // <= C_i

		// add constraint (4):
		// sum(j belongs Rk) x_ij <= n * y_ik       for all k = 1 .. r
		// sum(j belongs Rk) x_ij - n * y_ik <= 0   for all k = 1 .. r
		for (int k = 0; k < r; k++) {
			name.str(std::string());
			name << "dependent_decision_" << i * r + k + 1;
			dependent_decision.add(IloRange(env, -IloInfinity, 0, name.str().c_str())); // <= 0
		} // k (classes)
	} // i (knapsacks)

	// add constraint (2):
	// sum(i = 1 ... m) x_ij <= 1       for all j = 1 .. n
	for (int j = 0; j < n; j++) {
		name.str(std::string());
		name << "max_one_bin_x_" << j + 1;
		max_one_bin_x.add(IloRange(env, -IloInfinity, 1.0, name.str().c_str())); // <= 1
	} // j (items)

	// add constraint (3):
	// sum(i = 1 ... m) y_ik <= 1       for all k = 1 .. r
	for (int k = 0; k < r; k++) {
		name.str(std::string());
		name << "max_b_bin_y_" << k + 1;
		max_b_bin_y.add(IloRange(env, -IloInfinity, b[k], name.str().c_str())); // <= 1
	} // k (classes)

}

void add_columns(IloModel model, IloObjective obj, IloRangeArray capacity, IloRangeArray max_one_bin_x, IloRangeArray max_b_bin_y, IloRangeArray dependent_decision, IloNumVarArray x, IloNumVarArray y, int n, int m, int r, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, bool intflag) {
	IloEnv env = model.getEnv();

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			// the objective coefficient of x_ij is p_ij
			IloNumColumn column_x = obj(profits[i*n + j]);

			// constraint (1):
			// sum(j = 1 ... n) w_j * x_ij + sum(k = 1 ... r) s_k * y_ik <= C_i   for all i = 1 .. m
			column_x += capacity[i](weights[j]); // sum(j = 1 ... n) w_j * x_ij

			// add constraint (2):
			// sum(i = 1 ... m) x_ij <= 1       for all j = 1 .. n
			column_x += max_one_bin_x[j](1.0);


			// constraint (4):
			// sum(j belongs Rk) x_ij <= n * y_ik       for all k = 1 .. r
			for (int k = 0; k < r; k++) {

				int indexes_prev = k > 0 ? indexes[k - 1] : 0;
				for (int z = 0; z < indexes[k] - indexes_prev; z++) {

					if (classes[z + indexes_prev] == j) {
						column_x += dependent_decision[i*r + k](1.0); // sum(j belongs Rk) x_ij
					}

				} // j (items)
			} // k (classes)

			// create the proper variable for CPLEX, corresponding to x_ij:
			// x_ij is binary, therefore its LB is 0 and its UB is 1
			std::stringstream name;
			name << "x_" << i + 1 << "_" << j + 1;

			if (intflag == false) {
				IloNumVar var(column_x, 0, 1, IloNumVar::Float, name.str().c_str());
				// add this variable to the IloNumVarArray for x
				x.add(var);
			}
			else {
				IloNumVar var(column_x, 0, 1, IloNumVar::Bool, name.str().c_str());
				// add this variable to the IloNumVarArray for x
				x.add(var);
			}

			// clean up memory used for the object column
			column_x.end();

		} // j (items)

		for (int k = 0; k < r; k++) {
			// the objective coefficient of y_ik is 0
			IloNumColumn column_y = obj(0.0);

			// constraint (1):
			// sum(j = 1 ... n) w_j * x_ij + sum(k = 1 ... r) s_k * y_ik <= C_i   for all i = 1 .. m
			column_y += capacity[i](setups[k]); // sum(k = 1 ... r) s_k * y_ik 

			// constraint (4):
			// sum(j belongs Rk) x_ij <= n * y_ik       for all k = 1 .. r
			column_y += dependent_decision[i*r + k](-n); // - n * y_ik

			// constraint (3):
			// sum(i = 1 ... m) y_ik <= 1       for all k = 1 .. r
			column_y += max_b_bin_y[k](1.0); // sum(i = 1 ... m) y_ik

			// create the proper variable for CPLEX, corresponding to y_ik:
			// y_ik is binary, therefore its LB is 0 and its UB is 1
			std::stringstream name;
			name << "y_" << i + 1 << "_" << k + 1;

			if (intflag == false) {
				IloNumVar var(column_y, 0, 1, IloNumVar::Float, name.str().c_str());
				// add this variable to the IloNumVarArray for y
				y.add(var);
			}
			else {
				IloNumVar var(column_y, 0, 1, IloNumVar::Bool, name.str().c_str());
				// add this variable to the IloNumVarArray for y
				y.add(var);
			}

			// clean up memory used for the object column
			column_y.end();

		} // k (classes)
	} // i (knapsacks)
}