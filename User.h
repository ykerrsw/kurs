
#include <string>
#include  <vector>
#include <iostream>

#include "sha224.h"

using namespace std;

class User{
    private:
        string ID;
        string hash;
    public:
        bool СheckLogin(vector<string> Db_ID);
        bool CheckPassword(vector<string> Db_hash, vector<string> Db_ID, string SALT);
        
        string get_ID();
        void set_ID(string ID1);

        string get_hash();
        void set_hash(string hash1);

};
