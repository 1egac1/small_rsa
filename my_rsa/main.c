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
	mpz_t prime_one, prime_two, euler_func, lcm_of_primes, k, buffer;
	mpz_inits(prime_one, prime_two, euler_func, lcm_of_primes, k, buffer, NULL);
	mpz_generate_prime_number(prime_one);
	mpz_generate_prime_number(prime_two);
	
	// Generating open key
	mpz_mul(keys.n, prime_one, prime_two);
	mpz_set_ui(keys.e, 65537);

	// Calculating Euler function
	mpz_sub_ui(prime_one, prime_one, 1);
	mpz_sub_ui(prime_two, prime_two, 1);
	mpz_add(euler_func, prime_one, prime_two);

	// Generating private key
	mpz_lcm(lcm_of_primes, prime_one, prime_two);
	mpz_set_ui(k, 1);
	do
	{
		mpz_add_ui(k, k, 1);
		// Expression d = (lcm_from_primes * k + 1) / e
		mpz_mul(keys.d, k, lcm_of_primes);
		mpz_add_ui(keys.d, keys.d, 1);
		// Checking, is d divisible without remainder by e
		mpz_mod(buffer, keys.d, keys.e);
		if (!mpz_cmp_ui(buffer, 0))
		{
			mpz_div(keys.d, keys.d, keys.e);
		}
		if (mpz_cmp(keys.d, euler_func) >= 0)
		{
			fprintf(stderr, "Oopss... Function generated private key that bigger than Euler function from prime numbers!\n");
			return;
		}
	} while (mpz_cmp(keys.d, prime_one) < 0 || mpz_cmp(keys.d, prime_two) < 0); // Check. Is prime numbers less than d
}

int main(){
	rsa_keys_t keys;

	mpz_generate_rsa_keys(keys);

	gmp_printf("Module(open key):\t%Zd\n"
			"Degree(open key):\t%Zd\n"
			"Degree(private key):\t%Zd\n", keys.n, keys.e, keys.d);

	return 0;
}
