#ifndef LP2MOD_H_
#define LP2MOD_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

int convertLpToMod(int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes, char * modFilename);

#endif /* LP2MOD_H_ */