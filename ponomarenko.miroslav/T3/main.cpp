#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Polygon.hpp"
#include "Commands.hpp"

using namespace ponomarenko;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Polygon p;
        if (iss >> p) {
            polygons.push_back(std::move(p));
        }
    }

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "AREA") {
            areaCommand(polygons, iss);
        } else if (command == "COUNT") {
            countCommand(polygons, iss);
        } else if (command == "MAX") {
            maxCommand(polygons, iss);
        } else if (command == "MIN") {
            minCommand(polygons, iss);
        } else if (command == "LESSAREA") {
            lessAreaCommand(polygons, iss);
        } else if (command == "MAXSEQ") {
            maxSeqCommand(polygons, iss);
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
