#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <utility>

class server {
public:
    std::string hashish;
    std::string file_name = "data.txt";

    bool check_pass(const std::vector<std::string>& Db_password, const std::vector<std::string>& Db_ID, const std::string& SALT, const std::string& ID);
    std::pair<std::vector<std::string>, std::vector<std::string>> data_base();
    std::string generate_salt();
    void set_hash(std::string hash2);
    ~server();

};

