cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main VERSION 1.0)
add_executable(${PROJECT_NAME} main.cpp library.hpp cmdarg.hpp cmdarg.cpp log.hpp log.cpp steam_library.hpp steam_library.cpp)
