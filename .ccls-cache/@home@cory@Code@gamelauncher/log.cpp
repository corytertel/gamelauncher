#include "log.h"

/* ANSI escape color codes:
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107

ASCI Code Tests:
    printf("\n");
    printf("\x1B[31mTexting\033[0m\t\t");
    printf("\x1B[32mTexting\033[0m\t\t");
    printf("\x1B[33mTexting\033[0m\t\t");
    printf("\x1B[34mTexting\033[0m\t\t");
    printf("\x1B[35mTexting\033[0m\n");
    
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[37mTexting\033[0m\t\t");
    printf("\x1B[93mTexting\033[0m\n");
    
    printf("\033[3;42;30mTexting\033[0m\t\t");
    printf("\033[3;43;30mTexting\033[0m\t\t");
    printf("\033[3;44;30mTexting\033[0m\t\t");
    printf("\033[3;104;30mTexting\033[0m\t\t");
    printf("\033[3;100;30mTexting\033[0m\n");

    printf("\033[3;47;35mTexting\033[0m\t\t");
    printf("\033[2;47;35mTexting\033[0m\t\t");
    printf("\033[1;47;35mTexting\033[0m\t\t");
    printf("\t\t");
    printf("\n");
*/

void Log::standard(std::string msg) {
    printf("\x1B[37m%s\033[0m", msg.c_str());
}

void Log::info(std::string msg) {
    printf("\x1B[36m[INFO] - %s\033[0m", msg.c_str());
}

void Log::debug(std::string msg) {
    printf("\x1B[93m[DEBUG] - %s\033[0m", msg.c_str());
}

void Log::warning(std::string msg) {
    printf("\033[1;43;30m[WARNING] - %s\033[0m", msg.c_str());
}

void Log::error(std::string msg) {
    printf("\033[1;41;37m[ERROR] - %s\033[0m", msg.c_str());
}