#pragma once
#include <iostream>
#include <system_error>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <stdexcept>
using namespace std;

class calc{
private:
public:
vector<uint64_t> v;
uint32_t dl;
calc(vector<uint64_t> vector, uint32_t len);
calc() = delete;
uint64_t calculate();
};