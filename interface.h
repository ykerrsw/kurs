#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <unistd.h>

using namespace std;

class interface {
public:
    string ip;
    int port;
    string database;
    string logfile;
    
    interface(int argc, char** argv);
    interface() = delete;
    
    string get_ip(){
        return ip;}
        
        
    int get_port(){
        return port;}
    
    int help();
    
};

