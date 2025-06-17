// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "DataStruct.h"
#include "commands.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }

    std::vector<shubina::Polygon> polygons;
    shubina::Polygon poly;

    while (file >> poly) {
        if (file && poly.points.size() >= 3) { // Only push if read was successful and has enough points
            polygons.push_back(poly);
        }
        // Clear any failbit caused by invalid input
        if (file.fail() && !file.eof()) {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    auto commands = shubina::createCommandMap();
    std::string command;
    while (std::cin >> command) {
        try {
            shubina::executeCommand(commands, polygons, command, std::cin, std::cout);
        } catch (const std::exception& e) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}

