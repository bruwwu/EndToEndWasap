#include <iostream>
#include <openssl\crypto.h>
int
main() {
  std::cout << "OpenSSL version: " << OpenSSL_version(OPENSSL_VERSION) << std::endl;
  std::cout << "OpenSSL version number: " << OpenSSL_version_num() << std::endl;
  std::cout << "Hola profe" << std::endl;
  return 0;
}