#include "crypto_utils.h"

void generatePublicKey(PublicRSAKey pubKey)
{
  std::string fileName("rakesh-podder.publickey");
  std::ofstream output_file_stream(fileName, std::ios::trunc | std::ios::out);
  if (!output_file_stream.good())
  {
    std::cerr << "ERROR: cannot write file [ " << fileName << " ]" << std::endl;
    exit(1);
  }
  std::ostringstream output_string_stream;
  output_string_stream << pubKey.e;
  output_string_stream << ", ";
  output_string_stream << pubKey.n;
  output_string_stream << "\n";
  output_file_stream << output_string_stream.str();
  output_file_stream.close();
}

void generatePrivateKey(PrivateRSAKey privKey)
{
  std::string fileName("rakesh-podder.privatekey");
  std::ofstream output_file_stream(fileName, std::ios::trunc | std::ios::out);
  if (!output_file_stream.good())
  {
    std::cerr << "ERROR: cannot write to file [ " << fileName << " ]" << std::endl;
    exit(1);
  }
  std::ostringstream output_string_stream;
  output_string_stream << privKey.d;
  output_string_stream << ", ";
  output_string_stream << privKey.n;
  output_string_stream << "\n";
  output_file_stream << output_string_stream.str();
  output_file_stream.close();
}

int main(int argc, char *argv[])
{
  std::srand(std::time(nullptr));

  auto begin = high_resolution_clock::now();
  RSAKey rsaKey = generateRSAKey();
  auto stop = high_resolution_clock::now();
  auto total = duration_cast<microseconds>(stop - begin);

  cout << "------------------------ Time Report --------------------------------" << endl
       << endl;
  cout << "Total timee for RSA Key Generation: " << total.count() << " ms." << endl;
  cout << "-----------------------------------------------------------------------" << endl
       << endl;
  generatePublicKey(rsaKey.pubKey);
  generatePrivateKey(rsaKey.privKey);
  return 0;
}
