#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdint>

int main(int argc, char* argv[]) {

	clock_t t0 = clock();

	// Declarations
	const int N = 1000000;
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
			nums[i] = 0;
			a += 2;
		}

		x += 2;
	}

	std::ofstream f;
	f.open("primes.txt");
	for (i = 0; i < N; i++) {
		if (nums[i] > 0) { f << nums[i] << '\t'; }
	}
	f << std::endl;
	f.close();

	std::cout << "Time: " << double(clock() - t0) / CLOCKS_PER_SEC << " s \n";

	delete[] nums;
	return 0;
}
