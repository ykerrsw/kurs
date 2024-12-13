#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <random>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

using namespace std;
//namespace CPP = CryptoPP;

class server{
public:

    string hash;

    bool check_pass(vector<string> Db_password, vector<string> Db_ID, string SALT, string ID);
    string file_name = "data.txt";
    pair<vector<string>, vector<string>> data_base(string file_name);
    string generate_salt();
    void set_hash(string hash1);
    ~server();
};
