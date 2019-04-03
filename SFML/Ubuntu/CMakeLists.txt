cmake_minimum_required(VERSION 3.13)
project(Ubuntu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ubuntu
        Core.cpp
        Core.hpp
        Interface.cpp
        Interface.hpp
        main.cpp
        Queue.cpp
        Queue.hpp)
