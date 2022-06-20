// Module
// System
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <gmp.h>
// sys
#include <sys/time.h>
#include <sys/file.h>
// Homemade
//
// main()
int main(){
// Value
// Basic
    long   Loop  [1];
    time_t Seed;
    long   Level = 8;
    gmp_randstate_t Random_State;
	gmp_randinit_default(Random_State);
   // RSA
    mpz_t Buffer_mpz_1, Buffer_mpz_2, Prime_1, Prime_2, Phi, Common_Key, Public_Key, Private_Key;
	mpz_inits(Buffer_mpz_1, Buffer_mpz_2, Prime_1, Prime_2, Phi, Common_Key, Public_Key, Private_Key, NULL);
  // Implementation
   // RSA init
    // Prime_1
     sleep(1);
     time(&Seed);
     gmp_randseed_ui(Random_State, Seed);
     mpz_urandomb(Prime_1, Random_State, Level);
	 mpz_nextprime(Prime_1, Prime_1);
   // Prime_2
     sleep(1);
     time(&Seed);
     gmp_randseed_ui(Random_State, Seed);
     mpz_urandomb(Prime_2, Random_State, Level);
	 mpz_nextprime(Prime_2, Prime_2);
   // Phi
     mpz_sub_ui(Phi,          Prime_1, 1);
     mpz_sub_ui(Buffer_mpz_1, Prime_2, 1);
     mpz_mul(   Phi,          Phi,     Buffer_mpz_1);
    // Common_Key
     mpz_mul(Common_Key, Prime_1, Prime_2);
     //
    // Public_Key
     // Init random Public_Key
      do{
       sleep(1);
       time(&Seed);
       gmp_randseed_ui(Random_State, Seed);
       mpz_urandomb(Public_Key, Random_State, Level);
      }while(mpz_cmp(Public_Key, Phi) >= 0 || mpz_cmp_ui(Public_Key, 1) == 0);
      mpz_set(Buffer_mpz_2, Public_Key);
     // Pick Public_Key
      while(1){
       if(mpz_cmp(Public_Key, Phi) < 0){
        mpz_gcd(Buffer_mpz_1, Public_Key, Phi);
        if(mpz_cmp_ui(Buffer_mpz_1, 1) == 0) break;
        mpz_add_ui(Public_Key, Public_Key, 1);
       }else{
        mpz_set(Public_Key, Buffer_mpz_2);
        while(1){
         mpz_sub_ui(Public_Key, Public_Key, 1);
         if(mpz_cmp_ui(Public_Key, 1) == 0){
          printf("%d\n", __LINE__);
          mpz_clear(Buffer_mpz_1);
          mpz_clear(Buffer_mpz_2);
          mpz_clear(Prime_1);
          mpz_clear(Prime_2);
          mpz_clear(Phi);
          mpz_clear(Common_Key);
          mpz_clear(Public_Key);
          mpz_clear(Private_Key);
          return 1;
         }
         mpz_gcd(Buffer_mpz_1, Public_Key, Phi);
         if(mpz_cmp_ui(Buffer_mpz_1, 1) == 0) goto l_END_PK;
        }
       }
      }
      l_END_PK:;
    // Private_Key
     mpz_set_ui(Buffer_mpz_1, 1);
     mpz_set_ui(Private_Key,  2); char Switch = 'V';
     l_AGAIN:do{
      mpz_add_ui(Private_Key, Private_Key, 1);
      mpz_mul(Buffer_mpz_1, Public_Key,   Private_Key);
      mpz_mod(Buffer_mpz_1, Buffer_mpz_1, Phi);
     }while(mpz_cmp_ui(Buffer_mpz_1, 1) != 0);
     if(Switch == 'V'){
      Switch = 'X';
      mpz_set(Buffer_mpz_2, Private_Key);
      goto l_AGAIN;
     }
   // Encrypt & Decrypt
    mpz_set_ui(Buffer_mpz_1, 88);
    mpz_powm(Buffer_mpz_1, Buffer_mpz_1, Public_Key,  Common_Key);
    mpz_powm(Buffer_mpz_1, Buffer_mpz_1, Private_Key, Common_Key);
    gmp_printf("Prime_1     %Zd\n", Prime_1);
    gmp_printf("Prime_2     %Zd\n", Prime_2);
    gmp_printf("Public_Key  %Zd\n", Public_Key);
    gmp_printf("Private_Key %Zd\n", Private_Key);
    gmp_printf("Common_Key  %Zd\n", Common_Key);
    gmp_printf("Decrypted   %Zd\n", Buffer_mpz_1);
    printf("----------------------------------------------------\n");
    mpz_set_ui(Buffer_mpz_1, 88);
    mpz_powm(Buffer_mpz_1, Buffer_mpz_1, Public_Key,   Common_Key);
    mpz_powm(Buffer_mpz_1, Buffer_mpz_1, Buffer_mpz_2, Common_Key);
    gmp_printf("Prime_1     %Zd\n", Prime_1);
    gmp_printf("Prime_2     %Zd\n", Prime_2);
    gmp_printf("Public_Key  %Zd\n", Public_Key);
    gmp_printf("Private_Key %Zd\n", Buffer_mpz_2);
    gmp_printf("Common_Key  %Zd\n", Common_Key);
    gmp_printf("Decrypted   %Zd\n", Buffer_mpz_1);
  // Clean up
   mpz_clear(Buffer_mpz_1);
   mpz_clear(Buffer_mpz_2);
   mpz_clear(Prime_1);
   mpz_clear(Prime_2);
   mpz_clear(Phi);
   mpz_clear(Common_Key);
   mpz_clear(Public_Key);
   mpz_clear(Private_Key);
   return 0;
 }
