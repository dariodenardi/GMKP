#ifndef GMKP_CONCERT_H_
#define GMKP_CONCERT_H_

#include <ilcplex/ilocplex.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "CHECK_CONS.h"

int solveGMKP_CONCERT(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modelFilename, char * logFilename, int TL, bool intflag);

#endif /* GMKP_CONCERT_H_ */