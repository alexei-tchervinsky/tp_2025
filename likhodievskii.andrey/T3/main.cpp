#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "DataStruct.hpp"
#include "commands.hpp"

using namespace likhodievskii;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: Filename not provided!\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "ERROR: Cannot open file!\n";
        return 2;
    }
    std::vector<Polygon> polygons;
    Polygon poly;
    while (file >> poly) {
        polygons.push_back(poly);
    }

    auto commands = createCommandMap();

    std::string command;
    while (std::cin >> command) {
        try {
            executeCommand(commands, polygons, command, std::cin, std::cout);
        } catch (const std::invalid_argument &e) {
            if (std::string(e.what()) == "INVALID COMMAND") {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
