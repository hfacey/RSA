# RSA
C++ implementation of the RSA encryption algorithm
Author: Horace Facey (Sept 2016)

This project is comprised of multiple programs which work together to form the RSA algorithm. The command "make" will compile the whole project. Otherwise, if you want to compile and run a specific program, you may execute the following directions:

--keygen--
To compile: make keygen
To run: ./keygen <prime number> <prime number> <public key filename> <private key filename>

Discription: This program accepts two prime numbers and two files, and generates the public and private keys needed for the RSA algorithm, based on a computationally hard problem (factorization). You want the primes to be really large numbers.

--encrypt--
To complie: make encrypt
To run: ./encrypt <public key filename> <plaintext filename> <encrypted text filename>

Discription: This module accepts a public key, input and output file, and encrypts the input file using the RSA keys and algorithm.

--decrypt--
To compile: make decrypt
To run: ./ decrypt <private key filename> <encrypted text filename> <decrypted text filename>

Discription: This module accepts a private key, an encrypted input file and an output file and decrypts the encrypted file using the key and RSA algorithm.

--factorial--
To compile: make factorial
To run: ./factorial <number>

Discription:This module accepts a positive integer n and finds n! (n factorial)

Known issues:
-Numbers greater than 100,000 are not tested for primality so the onus is on the user to ensure that really large numbers are prime.