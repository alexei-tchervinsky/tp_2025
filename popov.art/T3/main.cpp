#include "file_io.h"
#include "commands.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Filename not provided" << std::endl;
        return 1;
    }
    
    std::vector<Polygon> polygons = readPolygonsFromFile(argv[1]);
    
    std::string command;
    while (std::getline(std::cin, command)) {
        processCommand(command, polygons);
    }
    
    return 0;
}
