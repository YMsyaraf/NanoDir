#include "NanoDir.h"

void NanoDir::setBackgroundColor() {
    int width = tb_width();
    int height = tb_height();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tb_change_cell(x, y, ' ', TB_DEFAULT, backgroundColor);
        }
    }
}


void NanoDir::changeColor(ColorOption bg, ColorOption text) {
    switch (bg) {
        case COLOR_BLUE: backgroundColor = TB_BLUE; break;
        case COLOR_GREEN: backgroundColor = TB_GREEN; break;
        case COLOR_RED: backgroundColor = TB_RED; break;
        case COLOR_YELLOW: backgroundColor = TB_YELLOW; break;
        case COLOR_WHITE: backgroundColor = TB_WHITE; break;
        case COLOR_BLACK: backgroundColor = TB_BLACK; break;
    }
    switch (text) {
        case COLOR_BLUE: textColor = TB_BLUE; break;
        case COLOR_GREEN: textColor = TB_GREEN; break;
        case COLOR_RED: textColor = TB_RED; break;
        case COLOR_YELLOW: textColor = TB_YELLOW; break;
        case COLOR_WHITE: textColor = TB_WHITE; break;
        case COLOR_BLACK: textColor = TB_BLACK; break;
    }
}



void NanoDir::drawBox(int x, int y, int width, int height, uint16_t fg, uint16_t bg) {
    for (int i = 0; i < width; ++i) {
        tb_change_cell(x + i, y, '-', fg, bg);
        tb_change_cell(x + i, y + height - 1, '-', fg, bg);
    }
    for (int i = 0; i < height; ++i) {
        tb_change_cell(x, y + i, '|', fg, bg);
        tb_change_cell(x + width - 1, y + i, '|', fg, bg);
    }
    tb_change_cell(x, y, '+', fg, bg);
    tb_change_cell(x + width - 1, y, '+', fg, bg);
    tb_change_cell(x, y + height - 1, '+', fg, bg);
    tb_change_cell(x + width - 1, y + height - 1, '+', fg, bg);
}


void NanoDir::drawUI() {
    setBackgroundColor();

    drawBox(0, 0, tb_width(), 3, textColor, backgroundColor);
    tb_print(1, 1, textColor | TB_BOLD, backgroundColor, "NanoDir - A Simple File Manager");

    for (int i = 0; i < tb_width(); ++i) {
        tb_change_cell(i, 3, '-', textColor, backgroundColor);
    }

    tb_print(1, 4, textColor, backgroundColor, "Current Directory:");
    tb_print(1, 5, textColor, backgroundColor, currentPath.string().c_str());

    for (int i = 0; i < tb_width(); ++i) {
        tb_change_cell(i, 6, '-', textColor, backgroundColor);
    }

    int height = tb_height();
    int visibleLines = height - 9;
    int start = std::max(0, selectedIndex - visibleLines / 2);
    int end = std::min(start + visibleLines, static_cast<int>(files.size()));

    for (int i = start; i < end; ++i) {
        if (std::find(selectedFiles.begin(), selectedFiles.end(), i) != selectedFiles.end()) {
            tb_print(1, 7 + i - start, TB_BLACK, TB_GREEN, files[i].c_str()); // Highlight selected files
        } else if (i == selectedIndex) {
            tb_print(1, 7 + i - start, TB_BLACK, TB_YELLOW, files[i].c_str()); // Highlight current selection
        } else {
            tb_print(1, 7 + i - start, textColor, backgroundColor, files[i].c_str());
        }
    }

    tb_print(1, tb_height() - 1, TB_GREEN, backgroundColor, ("Command:" + commandBuffer).c_str());
    tb_change_cell(9 + commandBuffer.length(), tb_height() - 1, '_', TB_GREEN, backgroundColor);

    // Indicate current mode
    if (currentMode == MODE_COMMAND) {
        tb_print(1, tb_height() - 2, TB_RED, backgroundColor, "Command Mode");
    } else {
        tb_print(1, tb_height() - 2, TB_GREEN, backgroundColor, "Navigation Mode");
    }
}





void NanoDir::tb_print(int x, int y, uint16_t fg, uint16_t bg, const char *str) {
    while (*str) {
        tb_change_cell(x++, y, *str++, fg, bg);
    }
}
