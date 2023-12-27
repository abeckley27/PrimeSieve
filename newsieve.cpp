#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdint>

void printarray(int64_t* a, int64_t len) {
	int_fast64_t i;
	for (i = 0; i < len; i++) {
		std::cout << a[i] << '\t';
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	//Finds prime numbers below N

	clock_t t0 = clock();
	int64_t N = 1000000;
	if (argc > 1) { N = std::stol(argv[1]); }

	int64_t i;
	bool* s = new bool[N+1];

	// 0 and 1 are not prime
	s[0] = 0;
	s[1] = 0;
	// assume everything else is
	for (i = 2; i < N; i++) { s[i] = 1; }

	int64_t x;

	for (x = 2; x < ceil(sqrt(N)); x++) {
		if (s[x]) {
			for (int64_t multiple = x * x; multiple < N + 1; multiple += x) {
				s[multiple] = 0;
			}
		}
	}

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

	std::cout << "Pi(" << N << ") = " << count << std::endl;

	clock_t t1 = clock();
	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";

	delete[] s;
	return 0;
}