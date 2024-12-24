/**
 * @file Errors.h
 * @brief Класс Errors для обработки и записи ошибок.
 */
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * @brief Класс для обработки и записи ошибок.
 *
 * Класс Errors предоставляет функциональность для записи информации об ошибках в лог-файл, а также
 * для управления именем файла лога.
 */
class Errors {
public:
    /**
     * @brief Возвращает имя файла лога ошибок.
     *
     * @return Строка, содержащая имя файла лога ошибок.
     */
    string get_File_Log();

    /**
     * @brief Устанавливает имя файла лога ошибок.
     *
     * @param file Имя файла лога ошибок.
     */
    void set_File_Log(string file);

    /**
     * @brief Записывает информацию об ошибке в лог-файл.
     *
     * @param flag Тип ошибки
     * @param info Описание ошибки
     */
    void error_recording(string flag, string info);

private:
    /** @brief Имя файла лога ошибок. */
    string File_Log;
};

