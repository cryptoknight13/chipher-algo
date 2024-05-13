#include "crypto_utils.h"

void decryptCipherText(PrivateRSAKey privKey, std::string &cipherText)
{
  char tmp[4];
  char *cBlock = (char *)calloc(mpz_sizeinbase(privKey.n, 10) + 2, sizeof(char));
  mpz_t c;
  mpz_init(c);

  FILE *inf = fopen("rakesh-podder.ciphertext", "r");
  FILE *file = fopen("rakesh-podder.plaintext", "w+");

  while (!feof(inf) && mpz_inp_str(c, inf, 10)) {
    mpz_t m;
    mpz_init(m);
    mpz_powm(m, c, privKey.d, privKey.n); 
    mpz_get_str(cBlock, 10, m);

    for (int i = 0; i < strlen(cBlock); i++) {
      if (cBlock[i] == '1') {
        tmp[0] = cBlock[i++];
        tmp[1] = cBlock[i++];
        tmp[2] = cBlock[i];
      } else {
        tmp[0] = cBlock[i++];
        tmp[1] = cBlock[i];
        tmp[2] = '\0';
      }
      tmp[3] = '\0';
      fprintf(file, "%c", atoi(tmp));
    }
  }
  fprintf(file, "\n");

  fclose(inf);
  fclose(file);

  free(cBlock);

  std::cout << "Decrypted chiphertext: 'rakesh-podder.plaintext'" << std::endl;
}
int main(int argc, char *argv[])
{
  std::cout << "-------------------------------------------" << std::endl;
  std::cout << " Asymmetric Key Decryption (RSA)" << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
  if (argc != 3) {
    std::cerr << "Command Style: ./asymmetrickey_decr <priv_key_file> <file_to_decrypt>" << std::endl;
    return 1;
  }    

  std::string privKeyFile(argv[1]);
  std::string cipherTextFile(argv[2]);

  std::string keyStr = readFile(privKeyFile);
  size_t idx = keyStr.find(',');
  std::string dStr(keyStr.substr(0, idx));
  std::string nStr(keyStr.substr(idx + 2));


  PrivateRSAKey privKey;
  mpz_set_str(privKey.d, dStr.c_str(), 10); // use base 10
  mpz_set_str(privKey.n, nStr.c_str(), 10); // use base 10
  std::string cipherText = readFile(cipherTextFile);
  decryptCipherText(privKey, cipherText);

  return 0;
}

