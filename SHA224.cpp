/*#include "SHA224.h" 

std::string SHA224_hash(std::string msg) {
    using namespace CryptoPP;
    SHA224 hash;
    // типа сюда запишем результат
    std::string digest;
    StringSource(msg, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));

    return digest;
}

