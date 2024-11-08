
cmake_minimum_required(VERSION 3.15)
project(v.pradinee)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(v.pradinee 
    v.pradinee.cpp      
    data_handling.cpp
    data_handling.h
    studentas.cpp
    studentas.h
    rezultatai.cpp
    rezultatai.h
)

target_include_directories(v.pradinee PRIVATE ${CMAKE_SOURCE_DIR})

