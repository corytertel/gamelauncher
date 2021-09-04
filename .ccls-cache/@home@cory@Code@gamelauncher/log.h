#pragma once
#include <iostream>
#include <string>

struct Log {
    //Methods
    static void standard(std::string msg);
    static void info(std::string msg);
    static void debug(std::string msg);
    static void warning(std::string msg);
    static void error(std::string msg); 
};