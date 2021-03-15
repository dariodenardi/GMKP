#ifndef GMKP_CPX_H_
#define GMKP_CPX_H_

#include <ilcplex/ilocplex.h>
#include <ilcplex/ilocplexi.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

void solveGMKP_CPX(IloModel, IloObjective, IloRangeArray, IloRangeArray, IloRangeArray, IloNumVarArray, IloNumVarArray, int, int, int, int *, int *, int *, int *, int *, int *);

#endif /* GMKP_CPX_H_ */