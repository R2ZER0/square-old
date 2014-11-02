cmake_minimum_required(VERSION 2.6)
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

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test.sqr
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.sqr
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test.sqr
)

add_executable(square main.c)
