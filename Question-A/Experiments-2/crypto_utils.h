#pragma once

#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <vector>
#include <string>
#include <numeric>
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

std::vector<std::bitset<8>> keyToBits(const std::vector<BYTE>& uniqueKey);
std::vector<BYTE> uniqueKeyIdentify(std::string key);
std::vector<BYTE> readBinaryFile(std::string fileName);
std::vector<BYTE> vigenereCipher(std::vector<BYTE> &text, std::vector<BYTE> &key);
std::vector<std::vector<BYTE>> generateMatrix(std::vector<BYTE> &data);
std::vector<int> keyTraversal(std::vector<BYTE>& key);
std::vector<std::vector<BYTE>> sortedMatrix(std::vector<int>& order, std::vector<BYTE>& data);
std::vector<BYTE> createCipher(std::vector<int>& order, std::vector<std::vector<BYTE>>& matrix);
std::vector<BYTE> decryptCipher(std::vector<std::vector<BYTE>> &matrix);
std::vector<BYTE> doubleTranspositionEncryption(std::vector<BYTE> &c1, std::vector<BYTE> &key1, std::vector<BYTE> &key2);
std::vector<BYTE> decryptTranspositionDecryption(std::vector<BYTE> &c1, std::vector<BYTE> &key1, std::vector<BYTE> &key2);
void OutputFile(std::vector<BYTE> &data, std::string &fileName);
std::string getFileName();

#endif