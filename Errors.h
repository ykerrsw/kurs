#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*
 * @brief Класс для обработки и записи ошибок.
 *
 * Класс Errors предоставляет функциональность для записи информации об ошибках в лог-файл, а также
 * для управления именем файла лога.
 */
class Errors{
    public:
        string get_File_Log();
        void set_File_Log(string file);

        void error_recording(string flag, string info);

    private:
        string File_Log; /*< Имя файла лога ошибок. */};
        
