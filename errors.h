#pragma once
#include <stdexcept>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class errors{
    public:
        string get_filelog();
        void set_filelog(string file);

        void error_recording(string flag, string info);

    private:
        string logfile;
};