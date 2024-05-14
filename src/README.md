# PathFinder

## Project Overview

The PathFinder application is a SFML application which can visualize some interesting path finding algorithms.

## Dependencies and Requirements

This project depends on SFML library for graphics. SFML will be automatically downloaded and built as part of the build process.

## Building from Source
- Make sure you have CMake (version 3.16 or higher) installed on your system.

- Clone the repository:
`git clone https://gitlab.mff.cuni.cz/teaching/nprg041/2023-24/repetenti/horvatno.git`

- Navigate to the project directory:
`cd project/src/PathFinder`

- Create a build directory:
```bash
mkdir build
cd build
```

- Generate the build files with CMake:
`cmake ..`

- Build the project:
`cmake --build .`

Run the executable:

`./bin/PathFinder`

## Documentation:

- Ensure that you have installed Doxygen on your system using the `doxygen --version` command.
- Run the command `doxygen doxygen.config` in the `project/src/PathFinder` folder to generate the documentation.
- The generated documentation will be located in the `html` directory. You can view the documentation by opening the `index.html` file in the `html` directory in a web browser, or using the following command: `./html/index.html` assuming you are in the PathFinder folder.

## Usage

Upon running the executable, you will be presented with a graphical user interface where you can visualize different path-finding algorithms.
