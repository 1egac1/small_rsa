#ifndef RSA_H
#define RSA_H

#include <gmp.h>

void mpz_generate_prime_number(mpz_t x);	// Generates prime number to variables x

typedef struct
{
	mpz_t n;	// First part of open key
	mpz_t e;	// Second part of open key
	mpz_t d;	// Private key
} rsa_keys_t;

void mpz_generate_rsa_keys(rsa_keys_t keys); // in developing

#endif
