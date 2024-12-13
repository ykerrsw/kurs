#include "interface.h"
#include "errors.h"
#include "server.h"
#include "calc.h"

using namespace std;

interface::interface(int argc, char **argv[])
{
    int opt;
    int option_index = 0;
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
            logFile = string(optarg);
        }
        else{
            logFile = string("Log.conf");
        }
        break;
                
        case 'h':
            help();
            
            return 1;
        
        default:
            // Некорректная опция
            cout << "некорректная опция\n";
            help();
            return 2;
        }
}
if(address == "" or port == 0 or database == "" or logFile == ""){
        cout << "были переданы пустые параметры" << endl;
        help();
        return 0;
    }
    listner l(port);
    errors e(logfile);
    listner::l.set_ip(ip);
    errors::e.
    listner::l.set_log(logfile);
    listner::l.set_db(database);
    
    l.Run();
    
}


//------------------------------------------------------------------------------------------------

void interface::help(){
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
}
//------------------------------------------------------------------------------------------------







