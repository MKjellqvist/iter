cmake_minimum_required(VERSION 3.28)
project(iter)

set(CMAKE_CXX_STANDARD 17)

add_executable(iter main.cpp
        forward_list.h
        forward_list.cpp)
