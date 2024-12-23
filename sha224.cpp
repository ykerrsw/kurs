#include "sha224.h"


std::string SHA224_hash(std::string msg) {
    using namespace CryptoPP;

    SHA224 hash;
    std::string digest;

    StringSource(msg, true,
        new HashFilter(hash,
            new HexEncoder(
                new StringSink(digest)
            )
        )
    );
    return digest;
}
