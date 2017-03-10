cmake_minimum_required(VERSION 3.5)
project(compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_custom_target(compiler COMMAND make file=test.cpp CLION_EXE_DIR=${PROJECT_BINARY_DIR})