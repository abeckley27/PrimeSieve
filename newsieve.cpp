#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdint>

// I forget why this is here
void printarray(int64_t* a, int64_t len) {
	int_fast64_t i;
	for (i = 0; i < len; i++) {
		std::cout << a[i] << '\t';
	}
	std::cout << std::endl;
}

// Find all prime numbers below N
int main(int argc, char* argv[]) {

	//Initialize
	const clock_t t0 = clock();
	int64_t N = 1000000;
	int64_t i;

	// Allow for the upper bound to be specified as an argument
	if (argc > 1) { N = std::stol(argv[1]); }

	//bitmap for primality
	bool* s = new bool[N+1];

	// 0 and 1 are not prime
	s[0] = 0;
	s[1] = 0;
	// assume everything else is
	for (i = 2; i < N; i++) { s[i] = 1; }

	int64_t x;

	//Remove multiples of primes
	for (x = 2; x < ceil(sqrt(N)); x++) {
		if (s[x]) {
			for (int64_t multiple = x * x; multiple < N + 1; multiple += x) {
				s[multiple] = 0;
			}
		}
	}

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
