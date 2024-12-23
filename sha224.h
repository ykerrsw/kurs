#include <iostream>
#include <vector>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

std::string SHA224_hash(std::string msg);
