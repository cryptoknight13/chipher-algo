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
  std::string pt("originalText");
  std::string sChipher("substitution-cipher-before-change");
  std::string dChipher("transpose-cipher-before-change");
  std::string sChipher1("substitution-cipher-after-change");
  std::string dChipher1("transpose-cipher-after-change");
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
  OutputFile(plainText, pt);
    // Ensure there's at least one byte to modify
  std::vector<BYTE> c1(vigenereCipher(plainText, key1));
  OutputFile(plainText, sChipher);
  std::vector<BYTE> c3(doubleTranspositionEncryption(c1, key1, key2));
  // std::cout << "************ Encryption is done ************" << std::endl;
  OutputFile(plainText, dChipher);
  OutputFile(c3, encryptedFile);
  
  if (!plainText.empty()) {
    // Create a mask for the third bit (bit positions are 0-indexed)
    BYTE mask = 0x04;  // 00000100 in binary
    plainText[0] ^= mask;  // Flip the third bit of the first byte
  }

  std::vector<BYTE> c4(vigenereCipher(plainText, key1));
  OutputFile(c4, sChipher1);
  std::vector<BYTE> c5(doubleTranspositionEncryption(c4, key1, key2));
  // std::cout << "************ Encryption is done ************" << std::endl;
  OutputFile(c5, dChipher1);
  return 0;
}
