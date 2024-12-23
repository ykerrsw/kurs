/*
 * @file main.cpp
 * @brief Главный файл программы.
 *
 * Этот файл содержит функцию main(), которая является точкой входа в программу.
 * Он создает объект класса `interface` и передает ему аргументы командной строки.
 */
#include <iostream>
#include <system_error>

#include "Interface.h"
using namespace std;

int main(int argc, char** argv)
{ 
    interface v(argc, argv);
    return 0;
}
   
    

