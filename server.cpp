#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <random>
#include <openssl/sha.h>
#include "errors.h"
#include "server.h"
using namespace std;
//namespace CPP = CryptoPP;


//--------------------------------------------------------------------------
//читает и сохраняет логин пароль в отдельных векторах Err
pair<vector<string>, vector<string>> server::data_base(string file_name){
    ifstream inputFile(file_name);
     vector<string> firstVector;
 	vector<string> secondVector;
errors err1;

if (!inputFile.is_open()){
    inputFile.close();
    err1.error_recording("критичная", "не удалось открыть базу данных");
    
}
else if(inputFile.peek() == std::ifstream::traits_type::eof()) {
    inputFile.close();
    err1.error_recording("критичная", "база данных пуста");}

else
{   string line;

    while (getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string first, second;
        
        // Чтение двух строк, разделенных пробелом
        if (std::getline(ss, first, ':') && std::getline(ss, second, ':')) {
            firstVector.push_back(first);
            secondVector.push_back(second);}}

    inputFile.close();
    return std::make_pair(firstVector, secondVector);
}};
//--------------------------------------------------------------------------
string server::generate_salt(){
    std::random_device rd;
    // для генерации 64-битных чисел
    std::mt19937_64 gen(rd()); 
    std::uniform_int_distribution<unsigned long long> dis(0, 0xFFFFFFFFFFFFFFFF); 

    unsigned long long random64bit = dis(gen);

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << random64bit; // Форматируем в шестнадцатеричную строку длиной 16 символов, дополняя нулями

return ss.str();}
//--------------------------------------------------------------------------
bool server::check_pass(vector<string> Db_password, vector<string> Db_ID, string SALT, string ID){
     int t = 0;
 for (size_t i = 0; i < Db_ID.size(); ++i) {
     if (Db_ID[i] == ID){
         t = i;}}                           //записали индекс s
 
string spp = SALT + Db_password[t];
SHA224_CTX ctx;
SHA224_Init(&ctx);
SHA224_Update(&ctx, spp.c_str(), spp.length()); // Добавляем данные для хеширования
unsigned char hash2[SHA224_DIGEST_LENGTH];
SHA224_Final(hash2, &ctx); // Записываем результат в hash2

// Преобразование массива байтов в шестнадцатеричную строку
std::stringstream ss;
for (int i = 0; i < SHA224_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash2[i]);
}
string hex_hash = ss.str();
 if (hash == hex_hash){
     return 1;}
     
 else{return 0;}}
 //--------------------------------------------------------------------------
void set_hash(string hash1){
    hash == hash1; }
