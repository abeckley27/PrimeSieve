#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <list>

using namespace std;

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

inline bool is_prime(int64_t x, int64_t l, int64_t* plist) {
	int64_t i, j;
	bool result = true;

	for (i = 0; i < l; i++) {
		if (x % plist[i] == 0) { result = false; }		
	}
	return result;
}

int64_t count_len(list<int64_t>& pl) {
	int64_t result = 0;
	int64_t* ptr;
	ptr = &pl.front();

	return *ptr; 
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

	// Copy the first set of primes into a new array
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
	x = N2;
	if (x % 2 == 0) { x++; }
	list<int64_t> primelist2;

	// WAAYYYY SLOWER	
	while (x < N1) 
	{
		if (is_prime(x, j, primelst)) { primelist2.push_front(x); }
		x += 2;
	}

	ofstream f;
	string fname = "primes_under_";
	fname += to_string(N1);
	fname += ".txt";
	f.open(fname);

	for (i = 0; i < j; i++) {
		f << primelst[i] << '\t';
	}
	f << endl;
	f.close();


	
	t1 = clock();
	std::cout << "Pi(" << N2 << ") = " << count << std::endl;
	std::cout << "Time: " << (double(t1) - double(t0)) / CLOCKS_PER_SEC << " s \n";
	return 0;
}

int primes_wmoreinputs(int argc, char* argv[]) {

	clock_t t0 = clock();
	clock_t t1;
	int_fast64_t N = 1000;
	if (argc == 2) { N = std::stol(argv[1]); }
	else {
		if (argc == 3)	// For input in scientific notation
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

		// No need to store every number. This could be done with a bit array
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
		for (j = 1; j < array_size; j++) 
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

