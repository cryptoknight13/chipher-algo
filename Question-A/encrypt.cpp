#include "crypto_utils.h"

int main(int argc, char *argv[])
{
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "************ Encryption in Progress ************" << std::endl;
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
  std::vector<std::bitset<8>> bitKey1 = keyToBits(key1);
  std::cout << "Key 1: " << std::string(key1.begin(), key1.end()) << std::endl;
  std::cout << "Bit representation of the unique key:\n";
    for (const auto& bits : bitKey1) {
        std::cout << bits << ' ';
    }
    std::cout << std::endl;
 
  std::vector<BYTE> key2 = uniqueKeyIdentify(secondKey);
  std::vector<std::bitset<8>> bitKey2 = keyToBits(key2);
  std::cout << "Key 2: " << std::string(key2.begin(), key2.end()) << std::endl;
  std::cout << "Bit representation of the unique key:\n";
    for (const auto& bits : bitKey2) {
        std::cout << bits << ' ';
    }
    std::cout << std::endl;

  std::string fileName = getFileName();
  
  std::vector<BYTE> plainText(readBinaryFile(fileName));
  std::cout << "Read " << plainText.size() << " bytes from file: '" << fileName << "'" << std::endl;
  
    // Vigenere Cipher Encryption
    std::vector<BYTE> c1 = vigenereCipher(plainText, key1);

    // Double Transposition Encryption
    std::vector<BYTE> c3 = doubleTranspositionEncryption(c1, key1, key2);
    std::cout << "************ Encryption is done ************" << std::endl;
    OutputFile(c3, encryptedFile);
    return 0;
}