#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <unistd.h>

#include "listener.h"
using namespace std;

class interface {
public:
    string ip;
    string port;
    string database;
    string logfile;
    
    interface(int argc, char *argv[]);
    interface() = delete;
    
    string get_ip(){
        return ip;}
        
    /*string get_hash(){
        return hash;} */
        
    string get_port(){
        return port;}
    
    void help();
    
};

