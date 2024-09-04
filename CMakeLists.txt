cmake_minimum_required(VERSION 3.0)

project(nanodir LANGUAGES C)

add_executable(nanodir main.c)

install(TARGETS nanodir RUNTIME DESTINATION bin)
