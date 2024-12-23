#pragma once
#include <memory>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "errors.h"
static constexpr int default_port = 33333;
static constexpr int default_qlen = 10;

class Listener
{

private:
    std::unique_ptr<sockaddr_in> self_addr;
    std::unique_ptr<sockaddr_in> foreign_addr;
    int queueLen;

public:

    //заполнены
    std::string ip;
    std::string logfile;
    std::string db;
    int port;
    
    std::string salt;
    std::string login;
    std::string hash;
    int sock;
    std::vector<uint64_t> vec;
     
    Listener(int port1, int qlen, std::string ip1);
    Listener() = delete;
    
    ~Listener(){
    close(sock);};
    
    void Run();
    
    void set_port(int prt1){
    errors err3;
    if (prt1 < 1023){
    err3.error_recording("критичная", "порт сервера должен быть больше 1024.");
    port = prt1;}};
    
    void set_ip(std::string ip1){
    ip = ip1;
    }

	void set_db(std::string db1){
    db = db1;
    }
	
	void set_log(std::string log){
    logfile = log;
    }

};
