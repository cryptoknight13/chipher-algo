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
