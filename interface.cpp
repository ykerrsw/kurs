#include <getopt.h>
#include "interface.h"
#include "errors.h"
#include "server.h"
#include "calc.h"
#include "listener.h"

using namespace std;

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
            {0,           0,                 0, 0}   
        };
        
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
        help();
    }
    int kolv = 3;
    Listener l(port, kolv, ip);
    errors e;
    //l.set_ip(ip);
    //std::cout<<ip<<endl;
    l.set_log(logfile);
    l.set_db(database);
    e.set_filelog(logfile);
    
    
    l.Run();
    
}


//------------------------------------------------------------------------------------------------

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







