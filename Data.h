/**
 * @file Data.h
 * @brief Класс Data для управления данными, связанными с файлами и клиентами.
 */
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Errors.h"

using namespace std;

/**
 * @brief Класс Data для управления данными, связанными с файлами и клиентами.
 *
 * Этот класс предназначен для хранения и обработки информации, связанной с чтением данных
 * из файла, а также для получения информации о клиентах, хранимой в двух векторах.
 */
class Data{
    public:
/**
     * @brief Возвращает имя файла, которое используется для чтения данных.
     *
     * @return std::string Имя файла, установленное с помощью set_FileReader.
     */
        string get_FileReader();
        void set_FileReader(string file);

        pair<vector<string>, vector<string>> getClient();
    private:
 /**
     * @brief Строка для хранения имени файла, которое используется для чтения данных.
     */
        string FileReader;
 /**
     * @brief Объект класса Errors для обработки ошибок.
     */
        Errors Err;
};
