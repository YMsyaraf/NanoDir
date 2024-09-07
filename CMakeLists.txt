cmake_minimum_required(VERSION 3.10)
project(NanoDir VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Define version macros globally
add_definitions(-DNANODIR_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DNANODIR_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DNANODIR_VERSION_PATCH=${PROJECT_VERSION_PATCH})

# Add common source files
set(COMMON_SOURCES
    src/common/NanoDir.cpp
    src/common/UI.cpp
    src/common/FileOperations.cpp
    src/common/InputHandler.cpp
)

# Add platform-specific source files
if (WIN32)
    add_executable(NanoDir src/windows/main_windows.cpp ${COMMON_SOURCES} ${SOURCE_FILES})
    find_path(TERMBOX_INCLUDE_DIR termbox.h PATHS "C:/path/to/termbox/include")
    find_library(TERMBOX_LIBRARY NAMES termbox PATHS "C:/path/to/termbox/lib")

    # Specify the location of the icon file
    set(ICON_FILE ${CMAKE_SOURCE_DIR}/assets/NanoDir.ico)

    # Add a custom command to copy the icon file to the build directory
    add_custom_command(
        TARGET NanoDir POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${ICON_FILE} $<TARGET_FILE_DIR:NanoDir>
    )
else()
    add_executable(NanoDir src/linux/main_linux.cpp ${COMMON_SOURCES})
    find_path(TERMBOX_INCLUDE_DIR termbox.h)
    find_library(TERMBOX_LIBRARY NAMES termbox)
endif()

include_directories(${TERMBOX_INCLUDE_DIR})
target_link_libraries(NanoDir ${TERMBOX_LIBRARY})
