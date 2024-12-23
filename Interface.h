#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <unistd.h>

using namespace std;
/*
 * @brief Класс interface для обработки аргументов командной строки и хранения конфигурационных данных.
 *
 *  Этот класс предназначен для обработки аргументов командной строки,
 *  полученных при запуске программы, и хранения конфигурационных данных, таких как IP-адрес,
 *  номер порта, имя файла базы данных и имя файла журнала ошибок.
 */
class interface {
public:
    string ip;	 /*< IP-адрес. */
    int port;	 /*< Порт. */
    string database;  /*< Название файла с базой данных. */
    string logfile;		/*< Название файла, куда записываются ошибки. */
    /*
     * @brief Конструктор, обрабатывающий аргументы командной строки.
     * 
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     */
    interface(int argc, char** argv);
    /*
     * @brief Запрещает создание объектов класса без аргументов.
     */
    interface() = delete;
     /*
     * @brief Возвращает IP-адрес.
     * @return IP-адрес.
     */
    string get_ip(){
        return ip;}
        
    /*
     * @brief Возвращает номер порта.
     * @return Номер порта.
     */    
    int get_port(){
        return port;}
    
    int help();
    
};

