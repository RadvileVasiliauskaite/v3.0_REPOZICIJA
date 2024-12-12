
cmake_minimum_required(VERSION 3.15)
project(v.pradinee)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/v.pradinee.cpp
	src/rezultatai.cpp
	src/studentas.cpp
	src/data_handling.cpp
)

add_executable(v.pradinee ${SOURCES})

target_include_directories(v.pradinee PRIVATE ${CMAKE_SOURCE_DIR}/headers)

