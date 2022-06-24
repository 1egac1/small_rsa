#include "rsa.h"
#include <gmp.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


void mpz_generate_prime_number(mpz_t x)
{ // Generates prime number to variables x
	gmp_randstate_t random_state;
	gmp_randinit_default(random_state);
	time_t seed;
	long size_level = 1059; // rrandomb generating number size of that = 2^size_level - 1, including
    sleep(1);
    time(&seed);
    gmp_randseed_ui(random_state, seed);
    mpz_rrandomb(x, random_state, size_level);
	mpz_nextprime(x, x);
	
}

void mpz_generate_rsa_keys(rsa_keys_t keys)
{

	// Initialization of keys parts
	mpz_inits(keys.n, keys.e, keys.d, NULL);

	// Generating two prime numbers
	mpz_t prime_one, prime_two, euler_func, lcm_of_primes;
	mpz_inits(prime_one, prime_two, NULL);
	mpz_generate_prime_number(prime_one);
	mpz_generate_prime_number(prime_two);
	
	// Generating module of key(open key part)
	mpz_mul(keys.n, prime_one, prime_two);

	// Generating degree(part of open key)
	mpz_sub_ui(prime_one, prime_one, 1);
	mpz_sub_ui(prime_two, prime_two, 1);
	mpz_lcm(lcm_of_primes, prime_one, prime_two);
	// At the same time calculating Euler function
	mpz_add(euler_func, prime_one, prime_two);
}

int main(){
	rsa_keys_t keys;


	gmp_printf("Module(open key):\t%Zd\n"
			"Degree(open key):\t%Zd\n"
			"Degree(private key):\t%Zd\n", keys.n, keys.e, keys.d);

	return 0;
}
