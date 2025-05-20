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
            // Read the polygon definition after the command
            std::string line;
            std::getline(std::cin, line);
            Polygon target = parsePolygon(line);

            if (target.points.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (cmd == "ECHO") {
                size_t count = handleEcho(polygons, target);
                std::cout << count << "\n";
            } else if (cmd == "INFRAME") {
                bool inFrame = handleInFrame(polygons, target);
                std::cout << (inFrame ? "YES" : "NO") << "\n";
            }
        } else {
            // Unknown command
            std::cout << "<INVALID COMMAND>\n";
            // Skip the rest of the line
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }
}
