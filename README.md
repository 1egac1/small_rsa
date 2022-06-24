# Implemintation of RSA in C language
## Generating keys ##
To generate the keys you must to create var of type ` rsa_keys_t `. Than you must to use function ` mpz_generate_rsa_keys(rsa_keys_t *x) ` to generate keys.
## Text ecryption/decryption ##
### Unsigned int encryption/decription ###
To encrypt ` unsigned int ` variable you must to use fucton
```
void mpz_rsa_enrypt_ui(rsa_keys_t *keys, unsigned int data, mpz_t output);
```
Cipher text will be saved in ` mpz_t ` variable ` output `.
To decrypt ` unsigned int ` variable you must to use function
```
void mpz_rsa_decrypt_ui(rsa_keys_t *keys, mpz_t input, unsigned int *output);
```
In ` output ` we will get source text.
