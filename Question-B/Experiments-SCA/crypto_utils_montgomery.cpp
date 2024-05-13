#include "crypto_utils.h"

std::string readFile(std::string &fileName)
{
  std::ifstream ifs(fileName, std::ios::in);
  if (!ifs.good()) {
    std::cerr << "ERROR: not able to open file '" << fileName << "'" << std::endl;
    exit(1);
  }

  std::string line;
  std::getline(ifs, line);
  ifs.close();

  return line;
}

void largePrime(mpz_t largePrime)
{
  char *str = new char[PRIMESIZE + 1];
  str[0] = '1';
  for (int i = 1; i < PRIMESIZE; i++) {
    int binary = (int)(rand() % 2);
    str[i] = binary + '0';
  }
  str[PRIMESIZE] = '\0';

  mpz_t primeNum;
  mpz_init(primeNum);
  mpz_set_str(primeNum, str, 2);
  mpz_nextprime(primeNum, primeNum);
  mpz_set(largePrime, primeNum);

  free(str);
}

void calculateTotient(mpz_t totient, mpz_t p, mpz_t q)
{
  mpz_t _totient, _p, _q;
  mpz_init(_totient);
  mpz_init(_p);
  mpz_init(_q);

  mpz_set(_p, p);
  mpz_sub_ui(_p, _p, 1);
  std::cout << "(p - 1): " << _p << std::endl;
  mpz_set(_q, q);
  mpz_sub_ui(_q, _q, 1);
  std::cout << "(q - 1): " << _q << std::endl;

  mpz_mul(_totient, _p, _q);
  mpz_set(totient, _totient);
}

bool isEValid(mpz_t totient, mpz_t e)
{
  mpz_t gcd;
  mpz_init(gcd);
  mpz_gcd(gcd, e, totient);
  if (mpz_cmp_ui(gcd, 1) == 0)
    return true;

  return false;
}

void findE(mpz_t totient, mpz_t e)
{
  unsigned long int _e = 65537;
  mpz_t gcd;
  mpz_init(gcd);
  
  while (true) {
    mpz_gcd_ui(gcd, totient, _e);
    if (mpz_cmp_ui(gcd, (unsigned long int)1) == 0)
      break;
    _e += 2;
  }
  
  mpz_set_ui(e, _e);
}
void findD(mpz_t e, mpz_t totient, mpz_t d)
{
  mpz_t _d;
  mpz_init(_d);
  if (!mpz_invert(_d, e, totient))
    std::cerr << "Could not find mpz_inverse" << std::endl;

  mpz_set(d, _d);
}
RSAKey generateRSAKey()
{
  RSAKey rsaKey;
  mpz_t p;
  mpz_init(p);
  largePrime(p);

  mpz_t q;
  mpz_init(q);
  largePrime(q);
  mpz_t n;
  mpz_init(n);
  mpz_mul(n, p, q);

  std::cout << "p: " << p << std::endl;
  std::cout << "q: " << q << std::endl;
  std::cout << "n: " << n << std::endl;
  mpz_t totient;
  mpz_init(totient);
  calculateTotient(totient, p, q);
  std::cout << "totient: " << totient << std::endl;
  mpz_t e;
  mpz_init(e);
  findE(totient, e);
  std::cout << "e: " << e << std::endl;
  mpz_t d;
  mpz_init(d);
  findD(e, totient, d);
  std::cout << "d: " << d << std::endl;

  PublicRSAKey pubKey;
  mpz_set(pubKey.e, e);
  mpz_set(pubKey.n, n);

  PrivateRSAKey privKey;
  mpz_set(privKey.d, d);
  mpz_set(privKey.n, n);

  rsaKey.pubKey = pubKey;
  rsaKey.privKey = privKey;

  return rsaKey;
}

// Computes: result = (a * b * R^-1) mod n, where R is a power of 2 greater than n
void montgomeryMul(mpz_t result, const mpz_t a, const mpz_t b, const mpz_t n, const mpz_t nPrime, const mpz_t R) {
    mpz_t t;
    mpz_init(t);
    mpz_mul(t, a, b); // t = a * b

    mpz_t m;
    mpz_init(m);
    mpz_mul(m, t, nPrime);
    mpz_mod(m, m, R); // m = (t * nPrime) mod R

    mpz_t mn;
    mpz_init(mn);
    mpz_mul(mn, m, n); // mn = m * n
    mpz_add(t, t, mn); // t = t + m * n
    mpz_div(t, t, R); // t = (t + m * n) / R

    if (mpz_cmp(t, n) >= 0) {
        mpz_sub(t, t, n);
    }

    mpz_set(result, t);

    mpz_clear(t);
    mpz_clear(m);
    mpz_clear(mn);
}

// Computes R and n' for Montgomery multiplication
void computeMontgomeryConstants(mpz_t R, mpz_t nPrime, const mpz_t n) {
    mpz_set_ui(R, 1);
    while (mpz_cmp(R, n) <= 0) {
        mpz_mul_ui(R, R, 2);
    }

    mpz_invert(nPrime, n, R); // nPrime = n^-1 mod R
    mpz_neg(nPrime, nPrime); // nPrime = -nPrime
}
// Implementation of montgomeryExp
void montgomeryExp(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod, const mpz_t R, const mpz_t nPrime) {
    mpz_t baseR;
    mpz_init(baseR);
    mpz_mul(baseR, base, R); // Convert base to Montgomery form
    mpz_mod(baseR, baseR, mod);

    mpz_set_ui(result, 1);
    mpz_mul(result, result, R); // Convert 1 to Montgomery form
    mpz_mod(result, result, mod);

    for (int i = mpz_sizeinbase(exp, 2) - 1; i >= 0; i--) {
        montgomeryMul(result, result, result, mod, nPrime, R);
        if (mpz_tstbit(exp, i) == 1) {
            montgomeryMul(result, result, baseR, mod, nPrime, R);
        }
    }

    // Convert result out of Montgomery form
    mpz_t one;
    mpz_init_set_ui(one, 1);
    montgomeryMul(result, result, one, mod, nPrime, R);

    mpz_clear(baseR);
    mpz_clear(one);
}
