#include <getopt.h>
#include "Interface.h"
#include "listener.h"

using namespace std;

/*
 * @file interface.cpp
 * Конструктор класса `interface`, который обрабатывает аргументы командной строки.
 * Она использует библиотечную функцию `getopt_long` для парсинга аргументов, предоставленных при запуске программы. 
 * Поддерживаются длинные и короткие варианты опций для задания IP-адреса
 * Если какая-либо из опций не указана, устанавливаются значения по умолчанию
 */
interface::interface(int argc, char** argv)
{
    int opt;
    int option_index = 0;
    
static struct option long_options[] = {
{"ip",       required_argument, 0, 'i'}, 
{"port",     required_argument, 0, 'p'}, 
{"debug",    no_argument,       0, 'd'},
{"logfile", required_argument, 0, 'l'}, 
{"help",     no_argument,       0, 'h'},
{0,           0,                 0, 0}  };
        
   // if (){}
    while ((opt = getopt_long(argc, argv, "i::p::d::l::h::", long_options, &option_index)) != -1) {

        switch (opt) {
        case 'i':                           
        if (optarg != nullptr) {
            ip = string(optarg);
            }
            else{
                ip = string("127.0.0.1");
            }
            break;
            
        case 'p':                        
            if (optarg != nullptr) {
                port = stoi(optarg);
            }
            else{
                port = stoi("33333");
            }
            break;
                
            case 'd':
        if (optarg != nullptr) {
            database = string(optarg);
        }
        else{
            database = string("DB.conf");
        }
        break;

     case 'l':
        if (optarg != nullptr) {
            logfile = string(optarg);
        }
        else{
            logfile = string("Log.conf");
        }
        break;
                
        case 'h':
            help();
        
        default:
            // Некорректная опция
            cout << "некорректная опция\n";
            help();
       
        }
}
if(ip == "" or port == 0 or database == "" or logfile == ""){
        cout << "были переданы пустые параметры" << endl;
        help();}
        
listener l;
l.set_address(ip);
l.set_port(port);
l.interaction(database, logfile);

    
}


//------------------------------------------------------------------------------------------------
/*
 * @brief Выводит справку по использованию программы на консоль.
 *
 * Эта функция отображает информацию о параметрах командной строки, которые может принимать программа,
 * а также пример их использования.
 *
 * @return 0, если справка выведена успешно.
 */
int interface::help(){
    cout <<" ==============================================================================================="<< endl;
    cout <<"                                           СПРАВКА"<< endl;
    cout <<" ==============================================================================================="<< endl;
    cout <<"Параметры:"<< endl;
    cout << "-i сетевой адрес сервера" << endl;
    cout << "-p порт сервера" << endl;
    cout << "-d файл с базой данных" << endl;
    cout << "-l файл для аутентификации" << endl;
    cout << "-h получение справки по использованию программы.\n" << endl;
    cout << "Пример:" << endl;
    cout << "-i 127.0.0.1  -p 33333  -d DB.conf  -l log.conf" << endl;
    cout <<" ==============================================================================================="<< endl;
    return 0;
}
//------------------------------------------------------------------------------------------------







