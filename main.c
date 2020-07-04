#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    long long n;
    long long d;
}priv_key_t;

typedef struct {
    long long n;
    long long e;
}pub_key_t;

long long ExtEuclid(long long a, long long b)
{
    long long x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
    while (a!=0) {
        q = gcd/a; r = gcd % a;
        m = x-u*q; n = y-v*q;
        gcd = a; a = r; x = u; y = v; u = m; v = n;
    }
    return y;
}

int checkPrime(int n) {
	int i;
	int m = n / 2;
	
	for (i = 2; i <= m; i++) {
		if (n % i == 0) {
			return 0; // Not Prime
		}
	}

	return 1; // Prime
}

void rsa_gen_keys(priv_key_t *private_key, pub_key_t *public_key){
    int prime_buffer[3];
    // Заполнение массива простыми числами, исполненное одним из худших
    // вариантов

    int a = 12;
    for (int i = 0; i < 3; i++){
        while (checkPrime(a)){
            srand(time(NULL));
            a = 50000 + rand() % 100000;
        }
    }

    long long q = prime_buffer[0];
    long long p = prime_buffer[1];

    long long n = p * q;
    long long phin = (q - 1) * (p - 1);
    int e = 65537;
    long long d = ExtEuclid(phin, e);

    private_key->n = n;
    public_key->n = n;

    private_key->d = d;
    public_key->e = e;
}

int main (){
    priv_key_t private_key;
    pub_key_t public_key;

    rsa_gen_keys(&private_key, &public_key);

    printf("modul = %d, public = %d, private = %d", private_key.n,
            public_key.e, private_key.d);

    return 0;
}
