#include "geometry.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: filename not provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line)) {
        Polygon poly;
        if (parsePolygon(line, poly)) {
            polygons.push_back(poly);
        }
    }

    std::string command;
    while (std::cin >> command) {
        if (command == "AREA") {
            std::string param;
            std::cin >> param;
            processAreaCommand(polygons, param);
        }
        else if (command == "MAX" || command == "MIN") {
            std::string param;
            std::cin >> param;
            processMaxMinCommand(polygons, command, param);
        }
        else if (command == "COUNT") {
            std::string param;
            std::cin >> param;
            processCountCommand(polygons, param);
        }
        else if (command == "RMECHO") {
            std::string line;
            std::getline(std::cin >> std::ws, line);
            processRmechoCommand(polygons, line);
        }
        else if (command == "INTERSECTIONS") {
            std::string line;
            std::getline(std::cin >> std::ws, line);
            processIntersectionsCommand(polygons, line);
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}