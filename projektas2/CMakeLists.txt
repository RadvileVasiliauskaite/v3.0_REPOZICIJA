
cmake_minimum_required(VERSION 3.15)
project(projektas2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(projektas2 
    projektas2.cpp      
    data_handling.cpp
    data_handling.h
    studentas.h
    rezultatai.cpp
    rezultatai.h
)

target_include_directories(projektas2 PRIVATE ${CMAKE_SOURCE_DIR})

