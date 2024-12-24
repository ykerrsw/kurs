/**
 * @file Data.cpp
 * @brief Класс Data для считывания данных клиентов из файла.
 */
#include "Data.h"

/*
 * @brief Читает данные клиентов из файла и возвращает их в виде пары векторов.
 *
 * Функция считывает данные клиентов из файла, указанного в `Data::get_FileReader()`.  
 * Данные в файле предполагаются в формате "ID:Пароль", по одной паре на строке.
 * Функция возвращает пару векторов: первый содержит ID клиентов, второй - их пароли.
 * При возникновении ошибок (невозможность открыть файл или пустой файл) записывается критическая ошибка
 * и выбрасывается исключение.
 *
 * @return Пара векторов: первый содержит ID клиентов, второй - их пароли.
 *
 * @throws std::invalid_argument Если файл не может быть открыт или пуст.
 */
pair<vector<string>, vector<string>> Data::getClient(){
vector<string> firstVector;	/*< Вектор для хранения ID клиентов. */
vector<string> secondVector; /*< Вектор для хранения паролей клиентов. */

ifstream inputFile(Data::get_FileReader());

if (!inputFile.is_open()){
inputFile.close();
Err.error_recording("критичная", "Fun: getClient. Файла с БД открыть невозможно.");
        
    }
    else if(inputFile.peek() == std::ifstream::traits_type::eof()) {
        inputFile.close();
        Err.error_recording("критичная", "Fun: getClient. Файл с БД пуст.");

    }
    
    else
    {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string first, second;
            
            // Чтение двух строк, разделенных пробелом
            if (std::getline(ss, first, ':') && std::getline(ss, second, ':')) {
                firstVector.push_back(first);
                secondVector.push_back(second);
            }
        }

        inputFile.close();
    }
    
    return std::make_pair(firstVector, secondVector);
}


//------------------------------------------------------------------------------
/*
 * @brief Возвращает имя файла, используемого для чтения данных.
 *
 * Эта функция возвращает строку, содержащую имя файла, из которого класс `Data` считывает данные.
 *
 * @return Строка, содержащая имя файла для чтения.
 */
string Data::get_FileReader(){
    return FileReader;
}
//------------------------------------------------------------------------------
/*
 * @brief Устанавливает имя файла для чтения данных.
 *
 * Эта функция устанавливает имя файла, из которого класс `Data` будет считывать данные.
 *
 * @param file Имя файла для чтения.
 */
void Data::set_FileReader(string file){
    FileReader = file;
}
//------------------------------------------------------------------------------
