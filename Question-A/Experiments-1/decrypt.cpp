
#include "crypto_utils.h"
#include <chrono>

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

  std::vector<BYTE> key1 = uniqueKeyIdentify(secondKey);
  std::cout << "Key 1: " << std::string(key1.begin(), key1.end()) << std::endl;

  std::vector<BYTE> key2 = uniqueKeyIdentify(secondKey);
  std::cout << "Key 2: " << std::string(key2.begin(), key2.end()) << std::endl;

  std::string fileName = encryptedFile;
 
  std::vector<BYTE> cipherText(readBinaryFile(fileName));
  std::cout << "Read " << cipherText.size() << " bytes from ciphertext '" << fileName << "'" << std::endl;
  
  // Double transposition decryption
  auto beginTime_T = std::chrono::high_resolution_clock::now();
  std::vector<BYTE> c1(decryptTranspositionDecryption(cipherText, key1, key2));
  auto endTime_T = std::chrono::high_resolution_clock::now();
  auto durationTime_T = std::chrono::duration_cast<std::chrono::milliseconds>(endTime_T - beginTime_T);

  auto beginTime_S = std::chrono::high_resolution_clock::now();
  std::vector<BYTE> plainText(vigenereCipher(c1, key1));
  auto endTime_S = std::chrono::high_resolution_clock::now();
  auto durationTime_S = std::chrono::duration_cast<std::chrono::milliseconds>(endTime_S - beginTime_S);

  std::cout << "************ Decryption is done ************" << std::endl;
  OutputFile(plainText, decryptedFile);

    auto duration_Time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime_S - beginTime_T);
    std::cout << "------------------------ Time Report --------------------------------" << std::endl;
    std::cout << "Vigenere Cipher Decryption: " << durationTime_S.count() << " ms." << std::endl;
    std::cout << "Double Transposition Decryption: " << durationTime_T.count() << " ms." << std::endl;
    std::cout << "Entire Decryption Process: " << duration_Time.count() << " ms." << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
 
  return 0;
}