cmake_minimum_required(VERSION 3.9)
project(Concurrent_Computing)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#add_library(file1 file2)

set(SOURSE_LIB1 file1.cpp)

add_library(file1 STATIC ${SOURSE_LIB1})


set(SOURSE_LIB2 file2.cpp)

add_library(file2 STATIC ${SOURSE_LIB2})


add_executable(Concurrent_Computing main.cpp)

target_link_libraries(Concurrent_Computing file1 file2)