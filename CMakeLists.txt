
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project (structures)
add_executable(structures src/main.cpp)
