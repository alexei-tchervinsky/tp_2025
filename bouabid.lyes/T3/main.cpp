#include "geometry.h"
#include "commands.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <functional>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error\n";
        return 1;
    }

    auto polygons = readPolygons(argv[1]);
    std::string cmd, subCmd;

    // Command handlers map
    std::map<std::string, std::function<void(void)>> cmdHandlers;

    // ECHO command
    cmdHandlers["ECHO"] = [&]() {
        std::string line;
        std::getline(std::cin, line);
        Polygon target = parsePolygon(line);

        if (target.points.empty() || target.points.size() < 3) {
            std::cout << "<INVALID COMMAND>\n";
        } else {
            size_t count = handleEcho(polygons, target);
            std::cout << count << "\n";
        }
    };

    // INFRAME command
    cmdHandlers["INFRAME"] = [&]() {
        std::string line;
        std::getline(std::cin, line);
        Polygon target = parsePolygon(line);

        if (target.points.empty() || target.points.size() < 3) {
            std::cout << "<INVALID COMMAND>\n";
        } else {
            bool inFrame = handleInFrame(polygons, target);
            std::cout << (inFrame ? "<TRUE>" : "<FALSE>") << "\n";
        }
    };

    // COUNT command
    cmdHandlers["COUNT"] = [&]() {
        if (!(std::cin >> subCmd)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (subCmd == "ODD") {
            std::cout << countOddPolygons(polygons) << "\n";
        } else if (subCmd == "EVEN") {
            std::cout << countEvenPolygons(polygons) << "\n";
        } else {
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
    };

    // AREA command
    cmdHandlers["AREA"] = [&]() {
        if (!(std::cin >> subCmd)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
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
    };

    // MAX command
    cmdHandlers["MAX"] = [&]() {
        if (!(std::cin >> subCmd)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
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
    };

    // Process commands
    while (std::cin >> cmd) {
        auto it = cmdHandlers.find(cmd);
        if (it != cmdHandlers.end()) {
            it->second(); // Call the handler function
        } else {
            std::cout << "<INVALID COMMAND>\n";
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }

    return 0;
}
