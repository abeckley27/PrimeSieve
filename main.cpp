#include <string>
#include "util.h"

int main(int argc, char* argv[]) {

    if (argc >= 2) {
        if (std::string(argv[1]) == "is_prime") {
            std::string start = std::string(argv[2]) + " is ";
            std::string primality = "";
            if ( !(is_prime( std::stoll(argv[2]) )) ) { primality = "not "; }
            std::cout << start << primality << "prime.\n";
        }

        if (std::string(argv[1]) == "count") {
            std::cout << "There are " << pi( std::stoll(argv[2]) ) << " primes below " << argv[2] << std::endl;
        }

        if (std::string(argv[1]) == "list") {
            std::cout << "Prime numbers below " << argv[2] << ": \n";
            const int64_t N = std::stoll(argv[2]);
            bool* s = run_sequential_sieve(N);
            int64_t* p_array = bitmap_to_array(s, N+1);
            int64_t length = primecount(s, N+1);
            printarray(p_array, length);

            delete[] s;
            delete[] p_array;
        }

        if (std::string(argv[1]) == "factorization") {
            std::cout << "The prime factorization of " << argv[2] << " is ";
            int64_t N = std::stoll(argv[2]);

            if (is_prime(N)) {
                std::cout << N << std::endl;
            }

            else {
                const int32_t root_N = int32_t( ceil( sqrt(N) ) );
                bool* s = run_sequential_sieve(root_N);
                int64_t* p_array = bitmap_to_array(s, root_N+1);
                int64_t length = primecount(s, root_N+1);
                delete[] s;

                int64_t i;

                //Find the smallest prime factor
                while (N % p_array[i] > 0) {
                    i++;
                }

                std::cout << p_array[i];
                N = N / p_array[i];

                //Find the other prime factors
                for (int64_t j = i; j < length; j++) {
                    while (N % p_array[j] == 0) {
                        std::cout << " * " << p_array[j];
                        N = N / p_array[j];
                    }
                }

                if (N > 1) { std::cout << " * " << N;}
                std::cout << std::endl;
                delete[] p_array;
            }

        }

    }

    else {
        const int N_demo = 100;
        bool* s = run_sequential_sieve(N_demo);
        int64_t* p_array = bitmap_to_array(s, N_demo);
        int32_t length = primecount(s, N_demo);

        std::cout << "Primes below " << N_demo << std::endl;
        printarray(p_array, length);

        delete[] s;
        delete[] p_array;
    }

    return 0;
}