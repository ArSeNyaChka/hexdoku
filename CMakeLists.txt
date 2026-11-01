cmake_minimum_required(VERSION 4.2)
project(hexdoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(hexdoku main.cpp
        field_generator.cpp
        config.h
)
