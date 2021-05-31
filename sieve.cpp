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
	int_fast64_t N = 1000;
	if (argc == 2) { N = std::stol(argv[1]); }
	else {
		if (argc == 3)
		{
			double co = std::stod(argv[1]);
			int ex = std::stoi(argv[2]);
			N = int64_t(co * pow(10, ex)) + 1;
			std::cout << N << std::endl;
		}
	}

	std::cout << "Finding primes below " << N << std::endl;

	if (N < 2e8) 
	{
		int_fast64_t arraylen = 2 + (N/2);
		std::cout << "Array length is " << arraylen << std::endl;
		int_fast64_t* nums = new int_fast64_t[arraylen];
		int_fast64_t i, j;

		std::cout << log10(N) << std::endl;

		for (i = 0; i < arraylen; i++) { nums[i] = 0; }
		

		// Set the odd numbers below N
		for (i = 1; i < N/2; i++) { nums[i] = 2 * i + 1; }

		//Remove multiples of x
		int_fast64_t x = 3;
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

		delete[] nums;
		t1 = clock();
	}
	else 
	{
		const int64_t array_size = 10000000;
		const int64_t num_arrays = ((N/2) / array_size) + int((N/2) % array_size > 0);
		int64_t** nums = new int64_t* [num_arrays];
		int i,j;

		std::cout << "Initialization complete: " << std::endl;
		std::cout << "Array size: " << array_size << " long ints\n";
		std::cout << "Number of arrays: " << num_arrays << std::endl;

		for ( i = 0; i < num_arrays; i++) { 
			nums[i] = new int64_t[array_size];
			for (j = 0; j < array_size; j++) { nums[i][j] = i * array_size + j * 2 + 1; }
		}

		std::cout << "Finished allocating arrays\n";
		int64_t x = 3;
		int64_t multiple = 1;

		while ( x <= N/3) 
		{
			multiple = x * x;

			while (multiple < N) 
			{
				i = (multiple-1) / (2 * array_size);
				nums[i][array_index(multiple, array_size)] = 0;
				multiple = multiple + (2 * x);
			}

			x += 2;
		}

		std::ofstream f;
		f.open("primes.txt");
		f << 2 << '\t';
		for (j = 0; j < array_size; j++) 
		{
			if (nums[0][j] > 0) {f << nums[0][j] << '\t';}
		}
		for (i = 1; i < num_arrays; i++) 
		{
			for (j = 0; j < array_size; j++) {
				if (nums[i][j] > 0) {f << nums[i][j] << '\t';}
			}
		}
		f.close();

		for ( i = 0; i < num_arrays; i++) { delete[] nums[i]; }
		delete[] nums;
		t1 = clock();
	}

	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";
	return 0;
}
