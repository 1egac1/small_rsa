#include "rsa.h"
#include <gmp.h>
#include <stdio.h>

int main(){
	rsa_keys_t keys;
	mpz_generate_rsa_keys(&keys);

	unsigned int data = 12345, output_ui;
	mpz_t output;
	mpz_init(output);

	mpz_rsa_enrypt_ui(&keys, data, output);
	mpz_rsa_decrypt_ui(&keys, output, &output_ui);

	gmp_printf("%Zx\n %lu\n", output, output_ui);

	return 0;
}
