#ifndef OPL_CONV_H_
#define OPL_CONV_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

int convertToOPL(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modFilename);

#endif /* OPL_CONV_H_ */