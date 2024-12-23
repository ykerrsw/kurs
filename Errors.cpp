#include "Errors.h"

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
string Errors::get_File_Log(){
    return File_Log;
}
//--------------------------------------------------------------------------------------------------
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
