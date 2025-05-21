#include "geometry.h"
#include "commands.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error\n";
        return 1;
    }

    auto polygons = readPolygons(argv[1]);
    std::string cmd, subCmd;

    while (std::cin >> cmd) {
        if (cmd == "ECHO") {
            std::string line;
            std::getline(std::cin, line);
            Polygon target = parsePolygon(line);

            if (target.points.empty() || target.points.size() < 3) {
                std::cout << "<INVALID COMMAND>\n";
            } else {
                size_t count = handleEcho(polygons, target);
                std::cout << count << "\n";
            }
        } else if (cmd == "INFRAME") {
            std::string line;
            std::getline(std::cin, line);
            Polygon target = parsePolygon(line);

            if (target.points.empty() || target.points.size() < 3) {
                std::cout << "<INVALID COMMAND>\n";
            } else {
                bool inFrame = handleInFrame(polygons, target);
                std::cout << (inFrame ? "<TRUE>" : "<FALSE>") << "\n";  // <-- Changed format
            }
        } else if (cmd == "COUNT") {
            if (!(std::cin >> subCmd)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (subCmd == "ODD") {
                std::cout << countOddPolygons(polygons) << "\n";
            } else if (subCmd == "EVEN") {
                std::cout << countEvenPolygons(polygons) << "\n";
            } else {
                // Try to parse as a number
                try {
                    int vertices = std::stoi(subCmd);
                    if (vertices < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        std::cout << countPolygonsByVertices(polygons, vertices) << "\n";
                    }
                } catch (const std::exception&) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        } else if (cmd == "AREA") {
            if (!(std::cin >> subCmd)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (subCmd == "ODD") {
                std::cout << std::fixed << std::setprecision(1) << calculateOddArea(polygons) << "\n";
            } else if (subCmd == "EVEN") {
                std::cout << std::fixed << std::setprecision(1) << calculateEvenArea(polygons) << "\n";
            } else if (subCmd == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    std::cout << std::fixed << std::setprecision(1) << calculateMeanArea(polygons) << "\n";
                }
            } else {
                // Try to parse as a number
                try {
                    int vertices = std::stoi(subCmd);
                    if (vertices < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        std::cout << std::fixed << std::setprecision(1) << calculateAreaByVertices(polygons, vertices) << "\n";
                    }
                } catch (const std::exception&) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        } else if (cmd == "MAX") {
            if (!(std::cin >> subCmd)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (subCmd == "AREA") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    std::cout << std::fixed << std::setprecision(1) << getMaxArea(polygons) << "\n";
                }
            } else if (subCmd == "VERTEXES") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    std::cout << getMaxVertices(polygons) << "\n";
                }
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        } else {
            std::cout << "<INVALID COMMAND>\n";
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }

    return 0;
}
