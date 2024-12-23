#include <string>
#include  <vector>
#include <iostream>

#include "sha224.h"

using namespace std;

/*
 * @brief Класс, представляющий пользователя системы.
 *
 * Класс User хранит информацию о пользователе (ID и хэш пароля) и предоставляет методы для проверки
 * подлинности пользователя. Обратите внимание, что хранение хэшей паролей напрямую в коде -
 * небезопасная практика. В реальных приложениях необходимо использовать более безопасные методы,
 * такие как bcrypt или Argon2, и хранить хэши в защищенной базе данных.
 */
class User{
    private:
        string ID;	/*< Идентификатор пользователя. */
        string hash;  /*< Хэш пароля пользователя. */
    public:
        bool СheckLogin(vector<string> Db_ID);
        bool CheckPassword(vector<string> Db_hash, vector<string> Db_ID, string SALT);
        
        string get_ID();
        void set_ID(string ID1);

        string get_hash();
        void set_hash(string hash1);

};
