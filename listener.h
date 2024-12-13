#pragma once
#include <memory>
#include <netinet/in.h>
#include <string>
#include <vector>
using namespace std;

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
    string ip;
    string logfile;
    string db;
    int port;
    
    string salt;
    string login;
    string hash;
    int sock;
    vector<uint64_t> vec;
    
    Listener(unsigned short port=default_port, int qlen=default_qlen);
    Listener() = delete;
    ~Listener();
    void Run();
    
    void set_port(int prt);
    void set_ip(string ip1);
    void set_db(string db1);
    void set_log(string log);
};
