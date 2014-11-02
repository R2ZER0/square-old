cmake_minimum_required(VERSION 2.6)
project(square)

add_executable(square main.cpp)

install(TARGETS square RUNTIME DESTINATION bin)
