cmake_minimum_required(VERSION 3.0)

project(nanodir)

add_executable(nanodir main.cpp)

install(TARGETS nanodir RUNTIME DESTINATION bin)
