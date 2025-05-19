#include "geometry.h"
#include "commands.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error\n";
        return 1;
    }

    auto polygons = readPolygons(argv[1]);
    std::string cmd;

    while (std::cin >> cmd) {
        if (cmd == "ECHO" || cmd == "INFRAME") {
            std::string line;
            std::getline(std::cin >> std::ws, line);
            Polygon target = parsePolygon(line);
            if (target.points.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (cmd == "ECHO") {
                std::cout << handleEcho(polygons, target) << '\n';
            } else {
                std::cout << (handleInFrame(polygons, target) ? "<TRUE>" : "<FALSE>") << '\n';
            }
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
