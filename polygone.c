#include <gmp.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int main()
{
	// Random state initializing
	gmp_randstate_t random_state;
	gmp_randinit_default(random_state);

	// Initializing variables 
	time_t seed;
	long size_level = 1024; // urandomb generating number size of that = 2^size_level - 1, including
	mpz_t prime_num; mpz_init(prime_num);

	// Generation prime number
    sleep(1);
    time(&seed);
    gmp_randseed_ui(random_state, seed);
    mpz_rrandomb(prime_num, random_state, size_level);
	mpz_nextprime(prime_num, prime_num);
	int length = 
	
	gmp_printf("%Zd\n%lu\n", prime_num, sizeof(prime_num));

	return 0;
}
