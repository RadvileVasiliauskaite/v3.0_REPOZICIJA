
cmake_minimum_required(VERSION 3.15)


project(v.pradinee VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(v.pradinee 
    v.pradinee.cpp      
    data_handling.cpp   
    studentas.cpp
    rezultatai.cpp
)

target_include_directories(v.pradinee PRIVATE ${CMAKE_SOURCE_DIR})

install(TARGETS v.pradinee DESTINATION bin)
