#ifndef NANODIR_H
#define NANODIR_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <termbox.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

namespace fs = std::filesystem;

enum ColorOption {
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_WHITE,
    COLOR_BLACK
};

enum Mode {
    MODE_NAVIGATION,
    MODE_COMMAND
};

class NanoDir {
public:
    NanoDir();
    ~NanoDir();
    void run();

private:
    std::vector<std::string> files;
    std::vector<int> selectedFiles;
    int selectedIndex;
    fs::path currentPath;
    std::string commandBuffer;
    uint16_t backgroundColor;
    uint16_t textColor;
    Mode currentMode;

    void listFiles(const fs::path& path);
    void drawBox(int x, int y, int width, int height, uint16_t fg, uint16_t bg);
    void drawUI();
    void tb_print(int x, int y, uint16_t fg, uint16_t bg, const char *str);
    void executeCommand(const std::string& command);
    void handleMouseEvent(const tb_event &event);
    void handleKeyPress(const tb_event &event);
    void setBackgroundColor();
    void changeColor(ColorOption bg, ColorOption text);

};

#endif // NANODIR_H
