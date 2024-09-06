cmake_minimum_required(VERSION 3.10)
project(NanoDir VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Add common source files
set(COMMON_SOURCES
    src/common/NanoDir.cpp
    src/common/UI.cpp
    src/common/FileOperations.cpp
    src/common/InputHandler.cpp
)

# Add platform-specific source files
if (WIN32)
    add_executable(NanoDir src/windows/main.cpp ${COMMON_SOURCES})
    find_path(TERMBOX_INCLUDE_DIR termbox.h PATHS "C:/path/to/termbox/include")
    find_library(TERMBOX_LIBRARY NAMES termbox PATHS "C:/path/to/termbox/lib")
else()
    add_executable(NanoDir src/linux/main.cpp ${COMMON_SOURCES})
    find_path(TERMBOX_INCLUDE_DIR termbox.h)
    find_library(TERMBOX_LIBRARY NAMES termbox)
endif()

include_directories(${TERMBOX_INCLUDE_DIR})
target_link_libraries(NanoDir ${TERMBOX_LIBRARY})
