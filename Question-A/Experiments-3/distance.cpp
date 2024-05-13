#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

// Function to read the contents of a binary file into a string
std::string readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::string contents;
    char c;
    while (file.get(c)) {
        contents += c;
    }

    return contents;
}

// Function to calculate the Hamming distance between two strings
int hammingDistance(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        std::cerr << "Strings must be of equal length\n";
        return -1; // Error code for unequal lengths
    }
    
    int distance = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}

// Function to calculate the bitwise difference between two strings
int bitwiseDifference(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        std::cerr << "Strings must be of equal length\n";
        return -1; // Error code for unequal lengths
    }
    
    int difference = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        std::bitset<8> bits1(str1[i]);
        std::bitset<8> bits2(str2[i]);
        difference += (bits1 ^ bits2).count(); // Count differing bits
    }
    return difference;
}

int main() {
    // File names
    std::string filename1 = "transpose-cipher-after-change";
    std::string filename2 = "transpose-cipher-before-change";

    // Read the contents of the binary files
    std::string contents1 = readBinaryFile(filename1);
    std::string contents2 = readBinaryFile(filename2);

    // Calculate Hamming distance
    int hammingDist = hammingDistance(contents1, contents2);
    if (hammingDist >= 0) {
        std::cout << "Hamming distance: " << hammingDist << std::endl;
    }

    // Calculate bitwise difference
    int bitwiseDiff = bitwiseDifference(contents1, contents2);
    if (bitwiseDiff >= 0) {
        std::cout << "Bitwise difference: " << bitwiseDiff << std::endl;
    }

    return 0;
}
