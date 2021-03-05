#ifndef GMKP_CPX_H_
#define GMKP_CPX_H_

#include <ilcplex/cplex.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

int solveGMKP_CPX(int n, int m, int r, int *p, int *w, int *C, int *s, int **Rk, double *objval, int TL, bool intflag);

#endif /* GMKP_CPX_H_ */