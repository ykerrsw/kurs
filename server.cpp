#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include "errors.h"
#include "server.h"

//читает и сохраняет логин пароль в отдельных векторах 
//читает и сохраняет логин пароль в отдельных векторах
std::pair<std::vector<std::string>, std::vector<std::string>> server::data_base(){   //!!
    std::ifstream inputFile(file_name);
    std::vector<std::string> firstVector;
    std::vector<std::string> secondVector;
    errors err1;

    if (!inputFile.is_open()) {
        inputFile.close();
        err1.error_recording("критичная", "не удалось открыть базу данных");
       return std::make_pair(firstVector, secondVector);
    } else if(inputFile.peek() == std::ifstream::traits_type::eof()) {
        inputFile.close();
        err1.error_recording("критичная", "база данных пуста");
        return std::make_pair(firstVector, secondVector);
    } else {
        std::string line;

        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string first, second;

            if (std::getline(ss, first, ':') && std::getline(ss, second, ':')) {
                firstVector.push_back(first);
                secondVector.push_back(second);
            }
        }

        inputFile.close();
        return std::make_pair(firstVector, secondVector);
    }
};
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
 bool server::check_pass(const std::vector<std::string>& Db_password, const std::vector<std::string>& Db_ID, const std::string& SALT, const std::string& ID) {
       size_t t = Db_ID.size();
       for (size_t i = 0; i < Db_ID.size(); ++i) {
           if (Db_ID[i] == ID) {
               t = i;
               break;
           }
       }
       if (t == Db_ID.size()) {
           return false;
       }

       std::string spp = SALT + Db_password[t];
       std::string hex_hash;

       using namespace CryptoPP;
       SHA224 hash;
       StringSource(spp, true,
                    new HashFilter(hash,
                                   new HexEncoder(
                                       new StringSink(hex_hash))));

       return hex_hash == hashish;
   }
 //--------------------------------------------------------------------------
void server::set_hash(string hash2){
    hashish == hash2; }
//---------------------------------------------------------------------------
 server::~server(){};
