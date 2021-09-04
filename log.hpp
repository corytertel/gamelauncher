#pragma once
#include <iostream>
#include <string>

struct Log {
    //Methods
    static void standard(const std::string& msg);
    static void info(const std::string& msg);
    static void debug(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg); 
};