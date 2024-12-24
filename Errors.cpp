/**
 * @file Errors.cpp
 * @brief Класс Errors для обработки ошибок и их записи в файл.
 */
#include "Errors.h"

/*
 * @brief Записывает информацию об ошибке в лог-файл.
 * 
 * Эта функция записывает информацию об ошибке в указанный файл логов. Если ошибка критическая,
 * то дополнительно выбрасывается исключение `std::invalid_argument`.
 *
 * @param flag Строка, указывающая тип ошибки (например, "критичная", "предупреждение").
 * @param info Строка, содержащая подробную информацию об ошибке.
 *
 * @throws std::invalid_argument Если флаг ошибки равен "критичная".
 */
void Errors::error_recording(string flag, string info){
    // Получаем текущую дату и время
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    if (flag == "критичная"){

        string logFileName = "log.conf";
        std::ofstream logFile(logFileName);
        if (logFile.is_open()) {
        // Записываем дату и время
        logFile << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " ";

        // Добавляем флаг (например, "ERROR")
        logFile << "  " << flag << "  ";

        // Записываем информацию об ошибке
        logFile << info << std::endl;

        // Закрываем файл
        logFile.close();
        }
        throw std::invalid_argument(info);
    }

    string logFileName = get_File_Log();
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        // Записываем дату и время
        logFile << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " ";

        // Добавляем флаг (например, "ERROR")
        logFile << flag << " ";

        // Записываем информацию об ошибке
        logFile << info << std::endl;

        // Закрываем файл
        logFile.close();}}
        
//--------------------------------------------------------------------------------------------------
/*
 * @brief Возвращает имя файла лога ошибок.
 * 
 * @return Строка, содержащая имя файла лога ошибок.
 */
string Errors::get_File_Log(){
    return File_Log;
}
//--------------------------------------------------------------------------------------------------
/*
 * @brief Устанавливает имя файла лога ошибок.
 *
 * Эта функция устанавливает имя файла, в который будут записываться ошибки.
 * Перед установкой проверяет существование и возможность открытия файла. 
 * Если файл не может быть открыт, записывает критическую ошибку в лог и выбрасывает исключение.
 *
 */
void Errors::set_File_Log(string file){

    ifstream inputFile(file);
	std::cout<<"файл "<<file<<" с журналом ошибок был успешно открыт"<<endl;
    if (!inputFile.is_open()){
        inputFile.close();
        error_recording("критичная", "Файл с журналом ошибок открыть невозможно.");
        
    }
    inputFile.close();
        File_Log = file;
}
