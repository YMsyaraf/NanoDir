#include "../common/NanoDir.h"

void showHelp() {
    std::cout << "NanoDir - A terminal-based file manager\n";
    std::cout << "Usage: nanodir [options] [directory]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help       Show this help message\n";
    std::cout << "  --version        Show version information\n";
}

void showVersion() {
    std::cout << "NanoDir version "
              << NANODIR_VERSION_MAJOR << "."
              << NANODIR_VERSION_MINOR << "."
              << NANODIR_VERSION_PATCH << "\n";
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            showHelp();
            return 0;
        } else if (arg == "--version") {
            showVersion();
            return 0;
        }
    }

    NanoDir app;

        // Check for debug flag
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--debug") {
            app.enableDebug();
            app.logDebug("Debug mode enabled");}
        }
    app.run();


    app.saveDebugLog();
    return 0;
}
