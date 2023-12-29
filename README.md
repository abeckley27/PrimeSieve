# PrimeSieve
Sieve of Eratosthenes in C++

The core features of the program are in main.cpp. On windows with gcc, run compile.bat. On other systems, compile main.cpp.

Syntax:

primes.exe is_prime 100   --> will determine if 100 is prime or not

primes.exe count 100   --> returns the number of primes below 100

primes.exe list 100    --> prints a list of all the prime numbers below 100


sieve.cpp and MPsieve.cpp are stand-alone programs that will find all prime numbers below a specified upper bound and then write the output to a file called primes.txt.

MPsieve is multithreaded, using OpenMP.
