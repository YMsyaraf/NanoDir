#include "NanoDir.h"

void NanoDir::executeCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd, dest;
    iss >> cmd >> dest;
    if (command == "exit") {
        tb_shutdown();
        exit(0);
    } else if (command.rfind("color ", 0) == 0) {
        std::istringstream iss(command);
        std::string cmd, bg, text;
        iss >> cmd >> bg >> text;
        ColorOption bgColor = COLOR_BLACK;
        ColorOption textColor = COLOR_WHITE;

        if (bg == "blue") bgColor = COLOR_BLUE;
        else if (bg == "green") bgColor = COLOR_GREEN;
        else if (bg == "red") bgColor = COLOR_RED;
        else if (bg == "yellow") bgColor = COLOR_YELLOW;
        else if (bg == "white") bgColor = COLOR_WHITE;
        else if (bg == "black") bgColor = COLOR_BLACK;

        if (text == "blue") textColor = COLOR_BLUE;
        else if (text == "green") textColor = COLOR_GREEN;
        else if (text == "red") textColor = COLOR_RED;
        else if (text == "yellow") textColor = COLOR_YELLOW;
        else if (text == "white") textColor = COLOR_WHITE;
        else if (text == "black") textColor = COLOR_BLACK;

        changeColor(bgColor, textColor);

    } else if (command == "delete") {
        for (int index : selectedFiles) {
            fs::remove(currentPath / files[index]);
        }
        selectedFiles.clear(); // Clear selection after operation

    } else if (command == "copy") {
        // Set destination to current directory
        fs::path destinationPath = dest.empty() ? currentPath : fs::path(dest);
        for (int index : selectedFiles) {
            fs::path source = currentPath / files[index];
            fs::path destination = destinationPath / files[index];

            // Check if the file already exists and add a number if it does
            int count = 1;
            while (fs::exists(destination)) {
                destination = destinationPath / (source.stem().string() + "(" + std::to_string(count) + ")" + source.extension().string());
                count++;
            }
            fs::copy(source, destination);
        }
        selectedFiles.clear(); // Clear selection after operation

    }else {
        tb_shutdown(); // Shutdown Termbox before executing the command
        chdir(currentPath.c_str()); // Change to the current directory
        int result = system(command.c_str());
        tb_init(); // Reinitialize Termbox after the command
        tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
        if (result != 0) {
            tb_print(1, tb_height() - 2, TB_RED, TB_BLUE, "Command failed");
        }
    }
    listFiles(currentPath); // Refresh the file list
}


void NanoDir::handleMouseEvent(const tb_event &event) {
    if (event.type == TB_EVENT_MOUSE) {
        if (event.key == TB_KEY_MOUSE_LEFT) {
            int mouseY = event.y;
            int visibleLines = tb_height() - 9;
            int start = std::max(0, selectedIndex - visibleLines / 2);
            //int end = std::min(start + visibleLines, static_cast<int>(files.size()));

            if (mouseY >= 7 && mouseY < 7 + visibleLines) {
                int index = start + (mouseY - 7);
                if (index < files.size()) {
                    selectedIndex = index;
                }
            }
        }
    }
}

void NanoDir::handleKeyPress(const tb_event &event) {
    if (event.key == TB_KEY_TAB) {
        // Switch between modes
        if (currentMode == MODE_NAVIGATION) {
            currentMode = MODE_COMMAND;
        } else {
            currentMode = MODE_NAVIGATION;
        }
        return;
    }

    if (currentMode == MODE_NAVIGATION) {
        switch (event.key) {
            case TB_KEY_ARROW_UP:
                if (selectedIndex > 0) {
                    selectedIndex--;
                }
                break;
            case TB_KEY_ARROW_DOWN:
                if (selectedIndex < files.size() - 1) {
                    selectedIndex++;
                }
                break;
            case TB_KEY_ENTER:
                if (files[selectedIndex] == "..") {
                    currentPath = currentPath.parent_path();
                } else {
                    fs::path newPath = currentPath / files[selectedIndex];
                    if (fs::is_directory(newPath)) {
                        currentPath = newPath;
                    }
                }
                listFiles(currentPath);
                selectedIndex = 0;
                break;
            case TB_KEY_SPACE:// Add this case for toggling selection
                {
                    auto it = std::find(selectedFiles.begin(), selectedFiles.end(), selectedIndex);
                    if (it != selectedFiles.end()) {
                        selectedFiles.erase(it); // Deselect if already selected
                    } else {
                    selectedFiles.push_back(selectedIndex); // Select if not already selected
                    }
                }
            break;
            default:
                break;
        }
    } else if (currentMode == MODE_COMMAND) {
        if (event.key == TB_KEY_ENTER) {
            executeCommand(commandBuffer);
            commandBuffer.clear();
            currentMode = MODE_NAVIGATION;
        } else if (event.key == TB_KEY_BACKSPACE || event.key == TB_KEY_BACKSPACE2) {
            if (!commandBuffer.empty()) {
                commandBuffer.pop_back();
            }
        } else if (event.ch) {
            commandBuffer.push_back(event.ch);
        } else if (event.key == TB_KEY_SPACE) {
            commandBuffer.push_back(' ');
        }
    }
}

