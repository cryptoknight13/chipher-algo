#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <bitset>
#include <cstdint>
#include <limits>

#define BYTE char
#define KEYSIZE 10
#define BYTE_LIMIT std::numeric_limits<BYTE>::max()


// ============================ Remove Duplicate Char & Find Unique Key======================================

std::vector<BYTE> uniqueKeyIdentify(std::string key)
{
    const int REQUIRED_KEY_SIZE = KEYSIZE;
    std::vector<BYTE> uniqueKey;
    std::locale loc;

    if (!std::all_of(key.begin(), key.end(), [](char c) { return std::isalpha(c); })) {
        std::cerr << "ERROR: Key must contain only English letters. Try again." << std::endl;
        exit(1);
    }

    if (key.size() < REQUIRED_KEY_SIZE) {
        std::cerr << "ERROR: Key [" << key << "] should be 10 characters long. Try again." << std::endl;
        exit(1);
    }
    for (int i = 0; i < key.size() && uniqueKey.size() < REQUIRED_KEY_SIZE; ++i) {
        BYTE c = std::toupper(key[i], loc);

        if (std::find(uniqueKey.begin(), uniqueKey.end(), c) == uniqueKey.end()) {
            uniqueKey.push_back(c); // Add unique character to the key
        }
    }
    if (uniqueKey.size() < REQUIRED_KEY_SIZE) {
        std::cerr << "ERROR: Key [" << key << "] should be 10 characters long. Try again." << std::endl;
        exit(1);
    }
    return uniqueKey;
}

std::vector<std::bitset<8>> keyToBits(const std::vector<BYTE>& uniqueKey) 
{
    std::vector<std::bitset<8>> bitRepresentation;
    for (BYTE character : uniqueKey) {
        bitRepresentation.push_back(std::bitset<8>(character)); // Convert each BYTE to its 8-bit form
    }
    return bitRepresentation;
}
// ================================= Read binary file ===========================================
/**
* 
*/
std::vector<BYTE> readBinaryFile(std::string fileName)
{
    std::ifstream fileStream(fileName, std::ios::binary | std::ios::in);
    if (!fileStream.good()) {
        std::cerr << "ERROR:'" << fileName << "' is Invalid!" << std::endl;
        exit(1);
    }

    fileStream.seekg(0, std::ios::end);
    std::streampos fileSize = fileStream.tellg();
    std::vector<BYTE> fileContents(fileSize);

    fileStream.seekg(0, std::ios::beg);
    fileStream.read(fileContents.data(), fileSize);
    fileStream.close();

    return fileContents;
}


// ===================================== Vigenere cipher =======================================
std::vector<BYTE>
vigenereCipher(std::vector<BYTE> &plainText, std::vector<BYTE> &key)
{
    std::vector<BYTE> cipherText;
    int keyIndex = 0;

    for (int i = 0; i < plainText.size(); i++) {
        BYTE plaintextByte = plainText[i];
        BYTE keyByte = key[keyIndex];
        BYTE mod = plaintextByte ^ keyByte;
        cipherText.push_back(mod);
        keyIndex = (keyIndex + 1) % key.size();
    }

    return cipherText;
}

std::vector<std::vector<BYTE>> generateMatrix(std::vector<BYTE> &data)
{
std::vector<std::vector<BYTE>> resultMatrix;
    std::vector<BYTE> row;

    if (data.size() < KEYSIZE) {
        for (auto& d : data)
            row.push_back(d);
        resultMatrix.push_back(row);
    } else {
        for (auto& d : data) {
            row.push_back(d);
            if (row.size() == KEYSIZE) {
                resultMatrix.push_back(row);
                row.clear();
            }
        }
        if (!row.empty())
            resultMatrix.push_back(row);
    }

    std::vector<BYTE>& lastRow = resultMatrix.back();
    int numToFill = KEYSIZE - lastRow.size();
    if (numToFill != 0) {
        for (int i = 0; i < numToFill; i++) {
            lastRow.push_back(BYTE_LIMIT);
        }
    }
    return resultMatrix;
}

std::vector<int> keyTraversal(std::vector<BYTE> &key)
{
    std::vector<BYTE> sortedKey(key);
    std::sort(sortedKey.begin(), sortedKey.end());

    std::vector<int> indexM;
    for (auto& sk : sortedKey) {
        auto it = std::find(key.begin(), key.end(), sk);
        if (it != key.end()) {
            indexM.push_back(std::distance(key.begin(), it));
        } else {
            std::cerr << "ERROR!\n";
        }
    }

    return indexM;
}

std::vector<std::vector<BYTE>> sortedMatrix(std::vector<int> &resultMatrix, std::vector<BYTE> &cipherText)
{
  int numRows = cipherText.size() / KEYSIZE;
  std::vector<std::vector<BYTE>> sorted_Matrix(numRows, std::vector<BYTE>(KEYSIZE));

    int currentRow = 0;
    auto columnIter = resultMatrix.begin(); 
    for (BYTE character : cipherText) {
        if (currentRow >= numRows) {
            currentRow = 0;
            ++columnIter;
        }
        sorted_Matrix[currentRow][*columnIter] = character;
        ++currentRow;
    }
    return sorted_Matrix;
}

std::vector<BYTE> createCipher(std::vector<int> &indexM, std::vector<std::vector<BYTE>> &matrix)
{
    std::vector<BYTE> cipherText;
    cipherText.reserve(matrix.size() * indexM.size());

    for (int column : indexM) {
        for (int row = 0; row < matrix.size(); ++row) {
            cipherText.push_back(matrix[row][column]);
        }
    }

    return cipherText;
}

std::vector<BYTE> decryptCipher(std::vector<std::vector<BYTE>> &matrix)
{
    if (matrix.empty()) return {};
    std::vector<BYTE> cipherText;
    size_t totalElements = 0;
    for (const auto& row : matrix) {
        totalElements += row.size();
    }
    cipherText.reserve(totalElements);
    for (const auto& row : matrix) {
        cipherText.insert(cipherText.end(), row.begin(), row.end());
    }
    return cipherText;
}

// ============================ Double transposition cipher (encryption) ================================================

std::vector<BYTE> doubleTranspositionEncryption(std::vector<BYTE> &vigenereCipherText,
                                            std::vector<BYTE> &key1, 
                                            std::vector<BYTE> &key2)
{
  // std::vector<std::vector<BYTE>> m1(generateMatrix(vigenereCipherText));
  // std::vector<int> keyOrder1(keyTraversal(key1));
  // std::vector<BYTE> c2(createCipher(keyOrder1, m1));
  // std::vector<std::vector<BYTE>> m2(generateMatrix(c2));
  // std::vector<int> keyOrder2 = keyTraversal(key2);
  // std::vector<BYTE> c3(createCipher(keyOrder2, m2));
  // std::vector<std::vector<BYTE>> m3(sortedMatrix(keyOrder2, c3));
  // std::vector<BYTE> d1(decryptCipher(m3));
  // if (d1 != c2) {
  //   std::cerr << "ERROR: transposition from second matrix to first cipher failed\n";
  //   std::cout << "C2: " << c2.size() << ": " << &c2[0] << std::endl;;
  //   std::cout << "D1: " << d1.size() << ": " << &d1[0] << std::endl;;
  // }
  // std::vector<std::vector<BYTE>> m4(sortedMatrix(keyOrder1, d1));
  // std::vector<BYTE> d2(decryptCipher(m4));
  // int numToRemove = d2.size() - vigenereCipherText.size();
  // if (numToRemove > 0) {
  //   for (int i = 0; i < numToRemove; i++)
  //     d2.pop_back();
  // }
  // if (d2 != vigenereCipherText) {
  //   std::cerr << "ERROR: transposition from first matrix to vegenere cipher failed\n";
  //   std::cout << "C1: " << vigenereCipherText.size() << ": " << &vigenereCipherText[0] << std::endl;;
  //   std::cout << "D2: " << d2.size() << ": " << &d2[0] << std::endl;;
  // }

  // return c3;
      // Generate first matrix and get key order for the first transposition
    std::vector<std::vector<BYTE>> matrix1 = generateMatrix(vigenereCipherText);
    std::vector<int> keyOrder1 = keyTraversal(key1);
    std::vector<BYTE> cipherText1 = createCipher(keyOrder1, matrix1);

    // Apply the second transposition
    std::vector<std::vector<BYTE>> matrix2 = generateMatrix(cipherText1);
    std::vector<int> keyOrder2 = keyTraversal(key2);
    std::vector<BYTE> cipherText2 = createCipher(keyOrder2, matrix2);

    // Reverse the process for verification
    std::vector<std::vector<BYTE>> reversedMatrix2 = sortedMatrix(keyOrder2, cipherText2);
    std::vector<BYTE> decryptedText1 = decryptCipher(reversedMatrix2);

    // Debugging and verification for the second transposition
    if (decryptedText1 != cipherText1) {
        std::cerr << "ERROR: Transposition from second matrix to first cipher failed\n";
    }

    std::vector<std::vector<BYTE>> reversedMatrix1 = sortedMatrix(keyOrder1, decryptedText1);
    std::vector<BYTE> decryptedText2 = decryptCipher(reversedMatrix1);

    // Handle potential excess bytes due to matrix padding
    decryptedText2.resize(vigenereCipherText.size());

    // Debugging and verification for the first transposition
    if (decryptedText2 != vigenereCipherText) {
        std::cerr << "ERROR: Transposition from first matrix to Vigenere cipher failed\n";
    }

    return cipherText2;
}

// ====================== Double transposition cipher (decryption)==============================================

std::vector<BYTE> decryptTranspositionDecryption(std::vector<BYTE> &cipherText,
                                             std::vector<BYTE> &key1, 
                                             std::vector<BYTE> &key2)
{
  // std::vector<int> keyOrder2 = keyTraversal(key2);
  // std::vector<std::vector<BYTE>> m3(sortedMatrix(keyOrder2, c1));
  // std::vector<BYTE> d1(decryptCipher(m3));

  // std::vector<int> keyOrder1(keyTraversal(key1));
  // std::vector<std::vector<BYTE>> m4(sortedMatrix(keyOrder1, d1));
  // std::vector<BYTE> d2(decryptCipher(m4));
  // //std::cout << "D2: " << d2.size() << ": " << &d2[0] << std::endl;;

  // auto ri = d2.rbegin();
  // auto rend = d2.rend();
  // for (; ri != rend; ++ri) {
  //   if (*ri == BYTE_LIMIT)
  //     d2.pop_back();
  //   else
  //     break;
  // }
  // return d2;
  // Reverse the second transposition
  std::vector<int> keyOrder2 = keyTraversal(key2);
  std::vector<std::vector<BYTE>> matrix2 = sortedMatrix(keyOrder2, cipherText);
  std::vector<BYTE> decryptedText1 = decryptCipher(matrix2);

  // Reverse the first transposition
  std::vector<int> keyOrder1 = keyTraversal(key1);
  std::vector<std::vector<BYTE>> matrix1 = sortedMatrix(keyOrder1, decryptedText1);
  std::vector<BYTE> decryptedText2 = decryptCipher(matrix1);

  // Trimming padding bytes (assuming BYTE_LIMIT is the padding byte)
  decryptedText2.erase(std::find_if(decryptedText2.rbegin(), decryptedText2.rend(),
                                      [](BYTE b) { return b != BYTE_LIMIT; }).base(),
                         decryptedText2.end());

  return decryptedText2;

}


std::string getFileName()
{
  std::string fileName;
  std::cout << "Binary File Name: ";
  std::getline(std::cin, fileName);
  return fileName;
}

void OutputFile(std::vector<BYTE> &data, std::string &fileName)
{
  std::ofstream ofs(fileName, std::ios::trunc | std::ios::binary | std::ios::out);
  if (!ofs.good()) {
    std::cerr << "ERROR:'" << fileName << "' not found!" << std::endl;
    exit(1);
  }

  ofs.write((const char*)&data[0], data.size());
  ofs.close();

  std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
  std::streampos fileSize;
  ifs.seekg(0, std::ios::end);
  fileSize = ifs.tellg();
  ifs.close();

  std::cout << "File: '" << fileName << " -> Bytes: " << fileSize << "" << std::endl;
}

