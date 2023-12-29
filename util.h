#ifndef utility_fns_h
#define utility_fns_h

#include <iostream>

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

#endif
