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

inline int_fast64_t array_index(int_fast64_t k) { return (k % 2) * (k-1) / 2; }

int main(int argc, char* argv[]) {

	clock_t t0 = clock();
	int_fast64_t N = 1000;
	if (argc > 1) { N = std::stoi(argv[1]); }

	int_fast64_t arraylen = 2 + (N/2);
	int_fast64_t* nums = new int_fast64_t[arraylen];
	int_fast64_t i, j;

	for (i = 0; i < arraylen; i++) { nums[i] = 0; }
	int_fast64_t x;

	// Set the odd numbers below N
	for (x = 1; x < N/2; x++) { nums[x] = 2 * x + 1; }

	//Remove multiples of x
	x = 3;
	while ( x <= N/3 ) 
	{
		int_fast64_t a = x;
		i = a * x;
		j = (i-1)/2;
		while (j < N/2) 
		{
			nums[j] = 0;
			a += 2;
			j = (a * x - 1) / 2;
		}

		x += 2;
	}

	std::ofstream f;
	f.open("primes.txt");
	f << 2 << '\t';

	for (i = 1; i < N/2; i++) {
		if (nums[i] > 0) { f << nums[i] << '\t'; }
	}
	f << std::endl;
	f.close();

	clock_t t1 = clock();
	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";

	delete[] nums;
	return 0;
}
