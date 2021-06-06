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

inline int_fast64_t array_index(int_fast64_t k, int_fast64_t len) {
	int_fast64_t k1 = (k-1) / 2;
	return k1 % len;
}

int main(int argc, char* argv[]) {

	clock_t t0 = clock();
	clock_t t1;
	int_fast64_t N1 = 1000;
	if (argc == 2) { N1 = std::stol(argv[1]); }
	else {
		if (argc == 3)
		{
			double co = std::stod(argv[1]);
			int ex = std::stoi(argv[2]);
			N1 = int64_t(co * pow(10, ex)) + 1;
			std::cout << N1 << std::endl;
		}
	}

	std::cout << "Finding primes below " << N1 << std::endl;
	// two step approach: 
	int_fast64_t N2 = int64_t( sqrt(N1) ) + 2;
	int_fast64_t arraylen = 2 + (N2/2);
	std::cout << "Array length is " << arraylen << std::endl;
	int_fast64_t* nums = new int_fast64_t[arraylen];
	int_fast64_t i, j;
	std::cout << log10(N2) << std::endl;
	for (i = 0; i < arraylen; i++) { nums[i] = 0; }
	
	// Set the odd numbers below N
	for (i = 1; i < N2/2; i++) { nums[i] = 2 * i + 1; }
	//Remove multiples of x
	int_fast64_t x = 3;
	while ( x <= N2/3 ) 
	{
		int_fast64_t a = x;
		i = a * x;
		j = (i-1)/2;
		while (j < N2/2) 
		{
			nums[j] = 0;
			a += 2;
			j = (a * x - 1) / 2;
		}
		x += 2;
	}
	int count = 1;
	for (i = 1; i < N2/2; i++) {
		if (nums[i] > 0) { count++; }
	}

	int64_t* primelst = new int64_t[count + 1];
	i = 0;
	j = 0;
	while (j < count) {
		if (nums[i] > 0) {
			primelst[j] = nums[i];
			j++;
		}
		i++;
	}

	delete[] nums;


	
	t1 = clock();
	std::cout << "Pi(" << N2 << ") = " << count << std::endl;
	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";
	return 0;
}
