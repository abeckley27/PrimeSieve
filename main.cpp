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

        if (std::string(argv[1]) == "prime_count") {
            std::cout << "There are " << pi( std::stoll(argv[2]) ) << " primes below " << argv[2] << std::endl;
        }

        if (std::string(argv[1]) == "list") {
            std::cout << "Prime numbers below " << argv[2] << ": \n";
            const int64_t N = std::stoll(argv[2]);
            bool* s = run_sequential_sieve(N);
            int64_t* p_array = bitmap_to_array(s, N);
            int64_t len = primecount(s, N);
            printarray(p_array, len);
        }

    }

    else {
        const int N_demo = 100;
        bool* s = run_sequential_sieve(N_demo);
        int64_t* p_array = bitmap_to_array(s, N_demo);
        int32_t len = primecount(s, N_demo);

        std::cout << "Primes below " << N_demo << std::endl;
        printarray(p_array, len);
    }

    return 0;
}