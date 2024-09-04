#ifndef NANODIR_H
#define NANODIR_H

#include <termbox.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

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
    int selectedIndex;
    fs::path currentPath;
    std::string commandBuffer;

    uint16_t backgroundColor;
    uint16_t textColor;
    Mode currentMode;

    void setBackgroundColor();
    void drawBox(int x, int y, int width, int height, uint16_t fg, uint16_t bg);
    void drawUI();
    void listFiles(const fs::path& path);
    void executeCommand(const std::string& command);
    void handleMouseEvent(const tb_event &event);
    void handleKeyPress(const tb_event &event);
    void tb_print(int x, int y, uint16_t fg, uint16_t bg, const char *str);
    void changeColor(ColorOption bg, ColorOption text);
};

#endif // NANODIR_H
