#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <gmp.h>
#include <sys/time.h>
#include <sys/file.h>


int main(){
	time_t seed;
	long   degree_n = 8;
	gmp_randstate_t rand_state;
	gmp_randinit_default(rand_state);
    mpz_t buffer_mpz_1, buffer_mpz_2, prime1, prime2, euler_func, common_key, pub_key, priv_key;
	mpz_inits(buffer_mpz_1, buffer_mpz_2, prime1, prime2, euler_func, common_key, pub_key, priv_key, NULL);

    // prime1
	sleep(1);
	time(&seed);
	gmp_randseed_ui(rand_state, seed);
	mpz_urandomb(prime1, rand_state, degree_n);
	mpz_nextprime(prime1, prime1);
	
	// prime2
	sleep(1);
	time(&seed);
	gmp_randseed_ui(rand_state, seed);
	mpz_urandomb(prime2, rand_state, degree_n);
	mpz_nextprime(prime2, prime2);

	// Euler's func
	mpz_sub_ui(euler_func,          prime1, 1);
	mpz_sub_ui(buffer_mpz_1, prime2, 1);
	mpz_mul(   euler_func,          euler_func,     buffer_mpz_1);

    // common_key
	mpz_mul(common_key, prime1, prime2);

    // pub_key
	// Init random pub_key
	do
	{
		sleep(1);
		time(&seed);
		gmp_randseed_ui(rand_state, seed);
		mpz_urandomb(pub_key, rand_state, degree_n);
	} while (mpz_cmp(pub_key, euler_func) >= 0 || mpz_cmp_ui(pub_key, 1) == 0);
	mpz_set(buffer_mpz_2, pub_key);

	// Pick pub_key
	while(1)
	{
		if(mpz_cmp(pub_key, euler_func) < 0)
		{
			mpz_gcd(buffer_mpz_1, pub_key, euler_func);
			if(mpz_cmp_ui(buffer_mpz_1, 1) == 0)
				break;
			mpz_add_ui(pub_key, pub_key, 1);
		}
		else
		{
			mpz_set(pub_key, buffer_mpz_2);
			while(1)
			{
				mpz_sub_ui(pub_key, pub_key, 1);
				if(mpz_cmp_ui(pub_key, 1) == 0)
				{
					printf("%d\n", __LINE__);
					mpz_clear(buffer_mpz_1);
					mpz_clear(buffer_mpz_2);
					mpz_clear(prime1);
					mpz_clear(prime2);
					mpz_clear(euler_func);
					mpz_clear(common_key);
					mpz_clear(pub_key);
					mpz_clear(priv_key);
					return 1;
				}
				mpz_gcd(buffer_mpz_1, pub_key, euler_func);
				if(mpz_cmp_ui(buffer_mpz_1, 1) == 0)
					goto l_END_PK;
			}
		}
	}
	l_END_PK:;
	// priv_key
	mpz_set_ui(buffer_mpz_1, 1);
	mpz_set_ui(priv_key,  2); char Switch = 'V';
	l_AGAIN:
	do
	{
		mpz_add_ui(priv_key, priv_key, 1);
		mpz_mul(buffer_mpz_1, pub_key,   priv_key);
		mpz_mod(buffer_mpz_1, buffer_mpz_1, euler_func);
	} while (mpz_cmp_ui(buffer_mpz_1, 1) != 0);
	if(Switch == 'V')
	{
		Switch = 'X';
		mpz_set(buffer_mpz_2, priv_key);
		goto l_AGAIN;
	}
	// Encrypt & Decrypt
	mpz_set_ui(buffer_mpz_1, 88);
	mpz_powm(buffer_mpz_1, buffer_mpz_1, pub_key,  common_key);
	mpz_powm(buffer_mpz_1, buffer_mpz_1, priv_key, common_key);
	gmp_printf("prime1     %Zd\n", prime1);
	gmp_printf("prime2     %Zd\n", prime2);
	gmp_printf("pub_key  %Zd\n", pub_key);
	gmp_printf("priv_key %Zd\n", priv_key);
	gmp_printf("common_key  %Zd\n", common_key);
	gmp_printf("Decrypted   %Zd\n", buffer_mpz_1);
	printf("----------------------------------------------------\n");
	mpz_set_ui(buffer_mpz_1, 88);
	mpz_powm(buffer_mpz_1, buffer_mpz_1, pub_key,   common_key);
	mpz_powm(buffer_mpz_1, buffer_mpz_1, buffer_mpz_2, common_key);
	gmp_printf("prime1     %Zd\n", prime1);
	gmp_printf("prime2     %Zd\n", prime2);
	gmp_printf("pub_key  %Zd\n", pub_key);
	gmp_printf("priv_key %Zd\n", buffer_mpz_2);
	gmp_printf("common_key  %Zd\n", common_key);
	gmp_printf("Decrypted   %Zd\n", buffer_mpz_1);
	// Clean up
	mpz_clear(buffer_mpz_1);
	mpz_clear(buffer_mpz_2);
	mpz_clear(prime1);
	mpz_clear(prime2);
	mpz_clear(euler_func);
	mpz_clear(common_key);
	mpz_clear(pub_key);
	mpz_clear(priv_key);
	return 0;
	}
