cmake_minimum_required(VERSION 3.10)

project(NanoDir VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the new source files
add_executable(NanoDir main.cpp NanoDir.cpp UI.cpp FileOperations.cpp InputHandler.cpp)

find_path(TERMBOX_INCLUDE_DIR termbox.h)
find_library(TERMBOX_LIBRARY NAMES termbox)

include_directories(${TERMBOX_INCLUDE_DIR})
target_link_libraries(NanoDir ${TERMBOX_LIBRARY})
