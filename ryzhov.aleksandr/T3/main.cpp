#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "DataStruct.hpp"
#include "commands.hpp"

using namespace ryzhov;

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
    while (!file.eof()) {
        Polygon poly;
        file >> poly;
        if (!file.fail() && !poly.points.empty()) {
            polygons.push_back(poly);
        }
    }

    auto commands = createCommandMap();

    std::string command;
    while (std::cin >> command) {
        try {
            executeCommand(commands, polygons, command, std::cin, std::cout);
        } catch (const std::invalid_argument &e) {
            std::cout << "<INVALID COMMAND>\n";
            if (std::string(e.what()) == "UNKNOWN COMMAND") {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    return 0;
}
