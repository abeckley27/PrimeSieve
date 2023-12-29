#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdint>
#include "util.h"

// Find all prime numbers below N
int main(int argc, char* argv[]) {

	//Initialize
	const clock_t t0 = clock();
	int64_t N = 1000000;
	int64_t i;

	// Allow for the upper bound to be specified as an argument
	if (argc > 1) { N = std::stoll(argv[1]); }

	bool* s = run_sequential_sieve(N);
	clock_t t1 = clock();

	// File output
	std::ofstream f;
	f.open("primes.txt");
	int64_t count = 0;

	for (i = 2; i < N; i++) {
		if (s[i]) { 
			f << i << '\t'; 
			count++;
		}
	}
	f << std::endl;
	f.close();

	delete[] s;

	std::cout << "Pi(" << N << ") = " << count << std::endl;
	clock_t t2 = clock();
	std::cout << "Calculation Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";
	std::cout << "Total Time: " << (double(t2) - double(t0)) / CLOCKS_PER_SEC << " s \n";

	return 0;
}
