cmake_minimum_required(VERSION 2.8)
project(square)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fmessage-length=0 -ansi -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Werror -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wwrite-strings -Winit-self -Wcast-align")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-qual -Wpointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-aliasing -Wformat=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-include-dirs")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wuninitialized")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wold-style-definition -Wstrict-prototypes")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes")

file(COPY ${CMAKE_SOURCE_DIR}/test.sqr
     DESTINATION ${CMAKE_BINARY_DIR}/test.sqr)

add_executable(square main.c utf8.c text.c)
