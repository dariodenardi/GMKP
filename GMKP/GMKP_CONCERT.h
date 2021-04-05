#ifndef GMKP_CONCERT_H_
#define GMKP_CONCERT_H_

#include <ilcplex/ilocplex.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

void solveGMKP_CONCERT(int n, int m, int r, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modelFilename, char * logFilename, int TL, bool intflag);

#endif /* GMKP_CONCERT_H_ */