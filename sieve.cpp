#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdint>

void printarray(int64_t* a, int len) {
	int i;
	for (i = 0; i < len; i++) {
		std::cout << a[i] << '\t';
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {

	clock_t t0 = clock();
	int N = 1000;
	if (argc > 1) { N = std::stoi(argv[1]); }

	int_fast64_t* nums = new int_fast64_t[N];
	int i, j;

	for (i = 0; i < N; i++) { nums[i] = 0; }
	int_fast64_t x = 3;
	nums[2] = 2;

	// Set the odd numbers below N
	for (x = 3; x < N; x += 2) { nums[x] = x; }

	x = 3;

	// Remove multiples of x
	while ( x <= N/3 ) 
	{
		int_fast64_t a = x;
		i = x * x;
		while (i < N) 
		{
			i = a * x;
			if (i < N) { nums[i] = 0; }
			a += 2;
		}

		x += 2;
	}

	std::ofstream f;
	f.open("primes.txt");
	f << nums[2] << '\t';

	for (i = 3; i < N; i += 2) {
		if (nums[i] > 0) { f << nums[i] << '\t'; }
	}
	f << std::endl;
	f.close();

	clock_t t1 = clock();
	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";

	delete[] nums;
	return 0;
}
