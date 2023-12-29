#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdint>
#include <omp.h>

// Prints an array to console, for debugging
void printarray(int64_t* a, int64_t len) {
	int_fast64_t i;
	for (i = 0; i < len; i++) {
		std::cout << a[i] << '\t';
	}
	std::cout << std::endl;
}

// This function allocates memory
bool* run_sequential_sieve(const int64_t N) {
	//bitmap for primality
	bool* s = new bool[N+1];

	// 0 and 1 are not prime
	s[0] = 0;
	s[1] = 0;
	// assume everything else is
	int64_t i;
	for (i = 2; i < N; i++) { s[i] = 1; }


	//Remove multiples of primes
	for (int64_t x = 2; x < ceil(sqrt(N)); x++) {
		if (s[x]) {
			for (int64_t multiple = x * x; multiple < N + 1; multiple += x) {
				s[multiple] = 0;
			}
		}
	}

	return s;
}

// This function allocates memory
int64_t* bitmap_to_array(bool* s, int64_t len) {
	int64_t primecount = 0;
	int64_t i, j;

	for (i = 2; i < len; i++) { primecount += s[i]; }
	int64_t* output = new int64_t[primecount];
	j = 0;

	for (i = 2; i < len; i++) {
		if (s[i]) {
			output[j] = i;
			j++;
		}
	}

	return output;
}

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
