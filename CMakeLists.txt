cmake_minimum_required(VERSION 3.9)
project(Concurrent_Computing)

#set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wall  -pthread")



add_executable(Concurrent_Computing main.cpp)

target_link_libraries(Concurrent_Computing)
