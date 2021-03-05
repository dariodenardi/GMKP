// GMKP.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream> // input/output
#include <fstream> // read files
#include <chrono> // get hours

#include "GMKP_CPX.h"

using namespace std;

/*int main()
{
	// data for GMKP instance
	int n; // number of objects
	int m; // number of knapsacks
	int r; // number of subsets
	int *p; // array for linear profit term
	int *w; // array of weights
	int *C; // array of knapsack capacities
	int *s; // array of setup
	int **Rk; // array of classes

	// input data from command line
	string input; // instance file name
	string output; // output file name
	int TL = 100; // time limit in seconds
	bool intflag = false;

	// output data
	double objval = 0;
	int status = 0;

	// get main args ...
	//std::cout << "write the file name of instance: ";
	//std::cin >> input;
	//std::cout << "write the file name of output: ";
	//std::cin >> output;
	//std::cout << "write the time limit (in second): ";
	//std::cin >> TL;

	// read instance
	n = 6;
	p = (int *)malloc(sizeof(int)*n);
	w = (int *)malloc(sizeof(int)*n);
	std::cout << "numero di elementi: " << n << "\n";

	p[0] = 100;
	p[1] = 49;
	p[2] = 36;
	p[3] = 15;
	p[4] = 18;
	p[5] = 15;

	w[0] = 15;
	w[1] = 10;
	w[2] = 9;
	w[3] = 4;
	w[4] = 5;
	w[5] = 5;

	m = 2;
	C = (int *)malloc(sizeof(int)*m);
	std::cout << "numero di zaini: " << m << "\n";

	C[0] = 30;
	C[1] = 12;

	r = 2;
	s = (int *)malloc(sizeof(int)*r);
	std::cout << "numero di classi: " << r << "\n";

	s[0] = 1;
	s[1] = 2;

	Rk = (int **)malloc(sizeof(int)*r);
	Rk[0] = (int *)malloc(sizeof(int) * 4);
	Rk[0][0] = 0;
	Rk[0][1] = 1;
	Rk[0][2] = 3;
	Rk[0][3] = 5;
	Rk[1] = (int *)malloc(sizeof(int) * 2);
	Rk[1][0] = 2;
	Rk[1][1] = 4;

	auto start = std::chrono::system_clock::now();

	status = solveGMKP_CPX(n, m, r, p, w, C, s, Rk, &objval, TL, intflag);

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	// print output
	std::cout << "durata dell'operazione: " << elapsed_seconds.count() << "\n";
	//if (status) {
	//	printf("Si è verificato un errore! Errore numero: %d\n", status);
	//} else {
	//	printf("La funzione è stata eseguita correttamente\n");
	//	printf("Il risultato è: %f", objval);
	//}

	// free memory
	free(p);
	free(w);
	free(C);
	free(s);
	free(Rk);

	// close file
	

	return 0;
}*/