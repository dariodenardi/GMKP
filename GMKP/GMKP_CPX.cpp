#include "GMKP_CPX.h"

void add_rows(IloModel, IloRangeArray, IloRangeArray, IloRangeArray, IloNumVarArray, int, int, int, int *);
void add_columns(IloModel, IloObjective, IloRangeArray, IloRangeArray, IloRangeArray, IloNumVarArray, IloNumVarArray, int, int, int, int *, int *, int *, int *, int *, int *);

void solveGMKP_CPX(IloModel model, IloObjective obj, IloRangeArray capacity, IloRangeArray max_one_bin, IloRangeArray big_m, IloNumVarArray x, IloNumVarArray y, int n, int m, int r, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes) {

	add_rows(model, capacity, max_one_bin, big_m, y, m, n, r, capacities);
	add_columns(model, obj, capacity, max_one_bin, big_m, x, y, n, m, r, weights, profits, capacities, setups, classes, indexes);
}

void add_rows(IloModel model, IloRangeArray capacity, IloRangeArray max_one_bin, IloRangeArray big_m, IloNumVarArray y, int m, int n, int r, int * capacities) {
	IloEnv env = model.getEnv();

	for (int i = 0; i < m; i++) {
		std::stringstream name;
		// Add constraint (1):
		// sum(j = 1 ... n) w_j * x_ij + sum(k = 1 ... r) s_k * y_ik <= C_i   for all i = 1 .. m
		name << "capacity_" << i + 1;
		capacity.add(IloRange(env, -IloInfinity, capacities[i], name.str().c_str()));

		for (int k = 0; k < r; k++) {

			// l'if serve per evitare di scrivere un altro ciclo for al dir fuori di quello di m
			// Add constraint (2):
			// sum(i = 1 ... m) y_ik <= 1       for all k = 1 .. r
			if (i == 0) {
				name.str(std::string());
				name << "max_one_bin_" << k + 1;
				max_one_bin.add(IloRange(env, -IloInfinity, 1.0, name.str().c_str()));
			}

			// Add constraint (3):
			// sum(j appartiene Rk) x_ij <= n * y_ik       for all k = 1 .. r
			// sum(j appartiene Rk) x_ij - n * y_ik <= 0   for all k = 1 .. r
			name.str(std::string());
			name << "big_m_" << i * r + k + 1;
			big_m.add(IloRange(env, -IloInfinity, 0, name.str().c_str()));
		} // k (classes)
	} // i (knapsacks)
}

void add_columns(IloModel model, IloObjective obj, IloRangeArray capacity, IloRangeArray max_one_bin, IloRangeArray big_m, IloNumVarArray x, IloNumVarArray y, int n, int m, int r, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes) {
	IloEnv env = model.getEnv();

	for (int i = 0; i < m; i++) {
		// constraint (1):
		// sum(j = 1 ... n) w_j * x_ij <= C_i   for all i = 1 .. m
		for (int j = 0; j < n; j++) {
			// the objective coefficient of x_ij is p_ij
			IloNumColumn column_x = obj(profits[j]);

			// add variable x_ij with its weight
			column_x += capacity[i](weights[j]);

			// constraint (3):
			// sum(j belongs Rk) x_ij <= n * y_ik       for all k = 1 .. r
			// sum(j belongs Rk) x_ij <= 0              for all k = 1 .. r
			for (int k = 0; k < r; k++) {

				int indexes_prev = k > 0 ? indexes[k - 1] : 0;
				for (int z = 0; z < indexes[k] - indexes_prev; z++) {

					if (classes[z + indexes_prev] == j) {
						// add variable x_ij with coefficient 1.0
						column_x += big_m[i*r + k](1.0);
					}

				} // j (objects)
			} // k (classes)

			// create the proper variable for CPLEX, corresponding to x_ij:
			// x_ij is binary, therefore its LB is 0 and its UB is 1
			std::stringstream name;
			name << "x_" << i + 1 << "_" << j + 1;
			IloNumVar var(column_x, 0, 1, IloNumVar::Bool, name.str().c_str());

			// add this variable to the IloNumVarArray for x
			x.add(var);

			// clean up memory used for the object column
			column_x.end();

		} // j (objects)

		for (int k = 0; k < r; k++) {
			// sum(k = 1 ... r) s_k * y_ik <= C_i

			// the objective coefficient of y_ik is 0
			IloNumColumn column_y = obj(0.0);

			// add variable y_ik with its setup
			column_y += capacity[i](setups[k]);

			// constraint (3):
			// sum(j appartiene Rk) x_ij <= n * y_ik       for all k = 1 .. r
			// sum(j appartiene Rk) x_ij - n * y_ik <= 0   for all k = 1 .. r
			column_y += big_m[i*r + k](-n);

			// constraint (2):
			// sum(i = 1 ... m) y_ik <= 1       for all k = 1 .. r
			column_y += max_one_bin[k](1.0);

			// create the proper variable for CPLEX, corresponding to y_ik:
			// y_ik is binary, therefore its LB is 0 and its UB is 1
			std::stringstream name;
			name << "y_" << i + 1 << "_" << k + 1;
			IloNumVar var(column_y, 0, 1, IloNumVar::Bool, name.str().c_str());

			// add this variable to the IloNumVarArray for y
			y.add(var);

			// clean up memory used for the object column
			column_y.end();

		} // k (classes)
	} // i (knapsacks)
}