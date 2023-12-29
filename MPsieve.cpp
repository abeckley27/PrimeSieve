#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdint>
#include <omp.h>


// Find all prime numbers below N
int main(int argc, char* argv[]) {

	//Initialize
	const double t0 = omp_get_wtime();
	int64_t N = 1000000;

	// Allow for the upper bound to be specified as an argument
	if (argc > 1) { N = std::stol(argv[1]); }
	int num_td = 1;

	#pragma omp parallel
	{
		num_td = omp_get_num_threads();
	}

	std::cout << "Number of threads: " << num_td << std::endl;
	bool* s = new bool[N+1];
	s[0] = 0;
	s[1] = 0;
	for (int64_t i = 2; i < N+1; i++) { s[i] = 1; }

	#pragma omp parallel for schedule(dynamic, 1)
	for (int64_t x = 2; x < int64_t(ceil(sqrt(N))); x++) {
		if (s[x]) {
			for (int64_t multiple = x * x; multiple < N + 1; multiple += x) {
				s[multiple] = 0;
			}
		}
	}

	double t1 = omp_get_wtime();

	// File output
	std::ofstream f;
	f.open("primes.txt");
	int64_t count = 0;
	int64_t i;

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
	double t2 = omp_get_wtime();
	std::cout << "Calculation Time: " << t1 - t0  << " s \n";
	std::cout << "Total Time: " << t2 - t0 << " s \n";



	return 0;
}
