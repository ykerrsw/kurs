
#pragma one
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>
#include <random>

#include <string>
#include <locale>
#include <codecvt>

#include "Data.h"
#include <vector>
#include <numeric>
#include <limits>
#include <iostream>
#include "User.h"

using namespace std;

/**
 * @brief Класс listener, реализующий серверную часть приложения.
 *
 * Этот класс отвечает за установление соединения с клиентами, обработку их запросов и отправку ответов.
 */
class listener{
    public:
     /**
     * @brief Устанавливает взаимодействие с клиентами, обрабатывает их запросы и отправляет ответы.
     *
     * @param database Путь к файлу базы данных.
     * @param logFile Путь к файлу логов.
     * @return 0, если взаимодействие успешно установлено; иначе -1.
     */
        int interaction(string database, string logFile);
        
      /**
     * @brief Вычисляет среднее арифметическое значений в векторе vec.
     * @return Среднее арифметическое значений в векторе.
     */
        uint64_t sredn();
	 
        string get_address();
        void set_address(string address1);
 	/**
     * @brief Устанавливает номер порта сервера.
     * @param port1 Номер порта, который нужно установить.
     */
        int get_port();
        void set_port(int port1);
	
        vector<uint64_t> get_vec();
        void set_vec(vector<uint64_t> v);

        string get_salt();
        void set_salt();

        pair<vector<string>, vector<string>> get_DB_clients();
        void set_DB_clients(vector<string> login, vector<string> password);

    private:
        string address;		 			 /**< IP-адрес сервера. */
        int port;			 			 /**< Номер порта сервера. */
        vector<uint64_t> vec;			 /**< Вектор значений. */
        string salt;					 /**< Сгенерированная соль. */
        pair<vector<string>, vector<string>>DB_clients; /**< Пара векторов: логины и пароли пользователей. */
        Errors Err;						 /**< Объект для обработки ошибок. */
};
