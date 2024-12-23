#include "User.h"


bool User::СheckLogin(vector<string> Db_ID){
    for (size_t i = 0; i < Db_ID.size(); ++i) {
        if (Db_ID[i] == ID){
            return 1;}}
return 0;}

//------------------------------------------------------------------------------------------------
bool User::CheckPassword(vector<string> Db_password, vector<string> Db_ID, string SALT){
    int t = 0;
    for (size_t i = 0; i < Db_ID.size(); ++i) {
        if (Db_ID[i] == ID){
            t = i;
        }
    }
    
    string hashSHA224 = SALT + Db_password[t];
    string HASHSA224 = SHA224_hash(hashSHA224);
    //cout<<HASHSA224<<endl;
    if (HASHSA224 == hash){
        return 1;
    } 
    else{
        return 0;
    }
}
//------------------------------------------------------------------------------------------------
string User::get_ID(){
    return ID;
}
//------------------------------------------------------------------------------------------------
void User::set_ID(string ID1){
    ID = ID1;

}

//------------------------------------------------------------------------------------------------
string User::get_hash(){
    return hash;
}
//------------------------------------------------------------------------------------------------

void User::set_hash(string hash1){
    hash = hash1;
}
