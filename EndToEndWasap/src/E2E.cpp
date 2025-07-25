#include <iostream>
#include <openssl\crypto.h>
int
main() {
  std::cout << "OpenSSL version: " << OpenSSL_version(OPENSSL_VERSION) << std::endl;
  return 0;
}