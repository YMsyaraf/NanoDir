# NanoDir

**NanoDir** is a terminal-based file manager designed for efficiency and simplicity. It offers cross-platform compatibility and a user-friendly interface.

## Features

- **Cross-Platform Compatibility**: Runs smoothly on various operating systems.
- **Icon Implementation**: Customizable icons for a visually intuitive experience.
- **Termbox Integration**: Utilizes termbox for a responsive and user-friendly interface.
- **Multiple Modes**: Command mode, selection mode, and navigation mode, switchable using the Tab key.

## Modes and Commands

### Command Mode

- **Color Command**: Change the color scheme.
  ```sh
  color <background> <text>
  ```
  Example:
  ```sh
  color yellow black
  ```
  This command will change the background to yellow and the text to black. Other colors are also supported.

- **Copy Command**: Copy files.
  - In command mode, type `copy` to copy a file to the same directory.
  - In selection mode, press `space` to select multiple files, then type `copy` to copy them to the same directory.

- **Delete Command**: Delete files.
  - In command mode, type `delete` to delete a file.
  - In selection mode, press `space` to select multiple files, then type `delete` to delete them.

### Selection Mode

- Press `space` to select or deselect files.
- Use the `copy` and `delete` commands to perform actions on selected files.

### Navigation Mode

- Navigate through directories and files using arrow keys or other navigation commands.

## Installation

### Prerequisites

- Ensure you have the necessary dependencies installed:
  - Termbox

### Build and Install

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/NanoDir.git
    cd NanoDir
    ```

2. Build the project:
    ```sh
    make
    ```

3. Run the application:
    ```sh
    ./nanodir
    ```

## Usage

Provide a brief guide on how to use NanoDir. For example:

```sh
nanodir [options] [directory]
```

- `-h, --help`: Show help message
- `-v, --version`: Show version information
- `--debug`: enable debug mode

### Debug log:
The debug log file is named `nanodir_debug.log`. 

### Location:
- **On Unix-like systems (Linux, macOS)**: It is saved in the home directory, typically `~/nanodir_debug.log`.
- **On Windows**: It is saved in the user's profile directory, typically `C:\Users\<YourUsername>\nanodir_debug.log`.


## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Create a new Pull Request


