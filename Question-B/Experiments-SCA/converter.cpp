#include <iostream>
#include <vector>
#include <gmp.h>
#include <openssl/evp.h>

// Function to decode Base64 string using OpenSSL
std::vector<unsigned char> decodeBase64(const std::string& encoded) {
    // Calculate the length of the decoded data
    size_t len = 4 * ((encoded.length() + 3) / 4);
    std::vector<unsigned char> decoded(len);

    // Create a BIO chain for Base64 decoding
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new_mem_buf(encoded.c_str(), encoded.length());
    bio = BIO_push(b64, bio);

    // Disable newline decoding
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    // Perform decoding
    len = BIO_read(bio, decoded.data(), encoded.length());
    decoded.resize(len);

    // Free BIO resources
    BIO_free_all(bio);
    return decoded;
}

// Convert decoded bytes to mpz_t integer
void bytesToInteger(mpz_t result, const std::vector<unsigned char>& bytes) {
    mpz_import(result, bytes.size(), 1, sizeof(bytes[0]), 0, 0, bytes.data());
}

int main() {
    std::string base64Encoded = "MFMCAQACDQdZkcFAybLsUcjQHscCAwEAAQINBP34OrtngBN5ha/c2QIHAmrxlMd97QIHAwo7YjOZAwIHAbf+xvJOPQIHAJNaZSCx8wIHAkYi9UI2/g==";

    // Decode the Base64 string
    std::vector<unsigned char> decodedBytes = decodeBase64(base64Encoded);

    // Initialize GMP integer
    mpz_t myInteger;
    mpz_init(myInteger);

    // Convert bytes to mpz_t
    bytesToInteger(myInteger, decodedBytes);

    // Print the integer
    mpz_out_str(stdout, 10, myInteger);
    std::cout << std::endl;

    // Clear GMP integer
    mpz_clear(myInteger);

    return 0;
}
