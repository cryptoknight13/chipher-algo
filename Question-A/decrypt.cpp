
#include "crypto_utils.h"

int main(int argc, char *argv[])
{
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "************ Decryption in Progress ************" << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
  if (argc != 3) {
    std::cerr << "Command Style: ./encrypt <key_1> <key_2>" << std::endl;
    return 1;
  }    

  std::string firstKey(argv[1]);
  std::string secondKey(argv[2]);
  std::string encryptedFile("rakesh-podder-encrypted-str");
  std::string decryptedFile("rakesh-podder-decrypted-str");

  std::vector<BYTE> key1 = uniqueKeyIdentify(firstKey);
  std::cout << "Key 1: " << std::string(key1.begin(), key1.end()) << std::endl;

  std::vector<BYTE> key2 = uniqueKeyIdentify(secondKey);
  std::cout << "Key 2: " << std::string(key2.begin(), key2.end()) << std::endl;
  std::string fileName = encryptedFile;
  std::vector<BYTE> cipherText(readBinaryFile(fileName));
  std::cout << "Read " << cipherText.size() << " bytes from encrypted file '" << fileName << "'" << std::endl;

  std::vector<BYTE> c1(decryptTranspositionDecryption(cipherText, key1, key2));

  std::vector<BYTE> plainText(vigenereCipher(c1, key1));
  std::cout << "************ Decryption is done ************" << std::endl;
  OutputFile(plainText, decryptedFile);

  return 0;
}