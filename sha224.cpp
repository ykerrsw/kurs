/**
* @file sha224.cpp
* @brief Вычисляет SHA224 хэш для заданной строки.
*/
#include "sha224.h"

/*
 * @brief Вычисляет SHA224 хэш для заданной строки.
 * Использует библиотеку CryptoPP для вычисления SHA224 хэш-суммы строки.
 * Результат представлен в шестнадцатеричном формате.
 * @param msg Строка, для которой нужно вычислить хэш.
 * @return Шестнадцатеричное представление SHA224 хэш-суммы входной строки.
 */
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

