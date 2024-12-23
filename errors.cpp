#include "errors.h"

//--------------------------------------------------------------------------
string errors::get_filelog(){
    return logfile;}
//--------------------------------------------------------------------------
void errors::set_filelog(std::string file) {
    std::ofstream outputFile(file, std::ios::app);
    if (!outputFile.is_open()) {
        outputFile.close(); 
        error_recording("критичная", "невозможно открыть или создать журнал ошибок");
    }
    else {outputFile.close(); 
       logfile = file;}}
//--------------------------------------------------------------------------
void errors::error_recording(string flag, string info){
    
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

    string logFileName = get_filelog();
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        // Записываем дату и время
        logFile << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " ";

        // Добавляем флаг (например, "ERROR")
        logFile << flag << " ";

        // Записываем информацию об ошибке
        logFile << info << std::endl;

        // Закрываем файл
        logFile.close();
    }
}
