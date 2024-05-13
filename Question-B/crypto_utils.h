#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <gmp.h>
#include <gmpxx.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define KEYSIZE 4096
#define PRIMESIZE (KEYSIZE / 2)

// ************************** Public & Private Keys Data Structure ************************** 
struct PublicRSAKey
{
  mpz_t e;
  mpz_t n;
  PublicRSAKey()
  {
    mpz_init(e);
    mpz_init(n);
  };
};

struct PrivateRSAKey
{
  mpz_t d;
  mpz_t n;
  PrivateRSAKey()
  {
    mpz_init(d);
    mpz_init(n);
  };
};

struct RSAKey
{
  PublicRSAKey pubKey;
  PrivateRSAKey privKey;
};

// ========================= RSA functions  ===================================
void largePrime(mpz_t largePrime);
void calculateTotient(mpz_t totient, mpz_t p, mpz_t q);
bool isEValid(mpz_t totient, mpz_t e);
void findE(mpz_t totient, mpz_t e);
void findD(mpz_t e, mpz_t totient, mpz_t d);
RSAKey generateRSAKey();
std::string readFile(std::string &fileName);
// ============================================================================

#endif
