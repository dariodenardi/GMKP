#ifndef GMKP_CPX_H_
#define GMKP_CPX_H_

#include <ilcplex/ilocplex.h>
#include <ilcplex/ilocplexi.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

int solveGMKP_CPX(int n, int m, int r, int *p, int *w, int *C, int *s, int **Rk, double *objval, int TL, bool intflag);
void add_rows(IloModel, IloRangeArray, IloRangeArray, IloRangeArray, IloNumVarArray, int, int, int, int *);
void add_columns(IloModel, IloObjective, IloRangeArray, IloRangeArray, IloRangeArray, IloNumVarArray, IloNumVarArray, int, int, int, int *, int *, int *, int *, int *, int *);

#endif /* GMKP_CPX_H_ */