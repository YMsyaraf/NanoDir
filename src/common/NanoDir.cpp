#include "NanoDir.h"


NanoDir::NanoDir()
        : files(),
        selectedIndex(0),
        currentPath(fs::current_path()),
        commandBuffer(""),
        backgroundColor(TB_BLACK),
        textColor(TB_YELLOW),
        currentMode(MODE_NAVIGATION) {

    if (tb_init() != 0) {
        std::cerr << "Failed to initialize Termbox" << std::endl;
        exit(1);
    }
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
    listFiles(currentPath);
}



NanoDir::~NanoDir() {
    tb_shutdown();
}

// Enable debug mode
void NanoDir::enableDebug() {
    debugMode = true;
}

// Log a debug message
void NanoDir::logDebug(const std::string& message) {
    if (debugMode) {
        debugLog.push_back(message);
    }
}

// Print the debug log
void NanoDir::saveDebugLog() {
    if (debugMode) {
        #ifdef _WIN32
        std::string homeDir = getenv("USERPROFILE");
        #else
        std::string homeDir = getenv("HOME");
        #endif
        std::string filePath = homeDir + ("/nanodir_debug.log");
        std::ofstream debugFile(filePath);
        for (const auto& message : debugLog) {
            debugFile << message << std::endl;
        }
        debugFile.close();
    }
}

void NanoDir::run() {
    while (true) {
        tb_clear();
        drawUI();
        tb_present();

        struct tb_event event;
        tb_poll_event(&event);

        if (event.type == TB_EVENT_KEY) {
            if (event.key == TB_KEY_ESC) {
                break;
            }
            handleKeyPress(event);
        } else if (event.type == TB_EVENT_MOUSE) {
            handleMouseEvent(event);
        }
    }
}

