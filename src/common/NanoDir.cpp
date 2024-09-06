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


