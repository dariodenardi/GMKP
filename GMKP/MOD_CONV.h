#ifndef MOD_CONV_H_
#define MOD_CONV_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

int convertLpToMod(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modFilename);

#endif /* MOD_CONV_H_ */