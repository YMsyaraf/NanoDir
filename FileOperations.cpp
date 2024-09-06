#include "NanoDir.h"

void NanoDir::listFiles(const std::filesystem::path& path) {
    files.clear();
    std::vector<std::string> directories;
    std::vector<std::string> regularFiles;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        } else {
            regularFiles.push_back(entry.path().filename().string());
        }
    }

    // Sort directories and files separately
    std::sort(directories.begin(), directories.end());
    std::sort(regularFiles.begin(), regularFiles.end());

    // Combine directories and files, with directories first
    files.push_back(".."); // Parent directory
    files.insert(files.end(), directories.begin(), directories.end());
    files.insert(files.end(), regularFiles.begin(), regularFiles.end());
}
