#include "commands.h"
#include "polygon_operations.h"
#include "file_io.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <string>
void processCommand(const std::string& command, std::vector<Polygon>& polygons) {
    std::istringstream iss(command);
    std::string cmd;
    if (!(iss >> cmd)) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    auto printInvalid = []() { std::cout << "<INVALID COMMAND>" << std::endl; };
    try {
        if (cmd == "AREA") {
            std::string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            if (arg == "EVEN") {
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double acc, const Polygon& p) {
                        return acc + (p.points.size() % 2 == 0 ? calculateArea(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            }
            else if (arg == "ODD") {
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double acc, const Polygon& p) {
                        return acc + (p.points.size() % 2 != 0 ? calculateArea(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            }
            else if (arg == "MEAN") {
                if (polygons.empty()) {
                    printInvalid();
                    return;
                }
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double acc, const Polygon& p) { return acc + calculateArea(p); });
                std::cout << std::fixed << std::setprecision(1) << sum / polygons.size() << std::endl;
            }
            else {
                try {
                    int num = std::stoi(arg);
                    if (num < 3) throw std::invalid_argument("Invalid vertex count");
                    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        [num](double acc, const Polygon& p) {
                            return acc + (p.points.size() == static_cast<size_t>(num) ? calculateArea(p) : 0.0);
                        });
                    std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
                }
                catch (...) {
                    printInvalid();
                }
            }
        }
        else if (cmd == "COUNT") {
            std::string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            if (arg == "EVEN") {
                int count = std::count_if(polygons.begin(), polygons.end(),
                    [](const Polygon& p) { return p.points.size() % 2 == 0; });
                std::cout << count << std::endl;
            }
            else if (arg == "ODD") {
                int count = std::count_if(polygons.begin(), polygons.end(),
                    [](const Polygon& p) { return p.points.size() % 2 != 0; });
                std::cout << count << std::endl;
            }
            else {
                try {
                    int num = std::stoi(arg);
                    if (num < 3) throw std::invalid_argument("Invalid vertex count");
                    int count = std::count_if(polygons.begin(), polygons.end(),
                        [num](const Polygon& p) { return p.points.size() == static_cast<size_t>(num); });
                    std::cout << count << std::endl;
                }
                catch (...) {
                    printInvalid();
                }
            }
        }
        else if (cmd == "MAX" || cmd == "MIN") {
            if (polygons.empty()) {
                printInvalid();
                return;
            }
            std::string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            if (arg == "AREA") {
                auto compareArea = [](const Polygon& a, const Polygon& b) {
                    return calculateArea(a) < calculateArea(b);
                };
                auto it = (cmd == "MAX") 
                    ? std::max_element(polygons.begin(), polygons.end(), compareArea)
                    : std::min_element(polygons.begin(), polygons.end(), compareArea);
                std::cout << std::fixed << std::setprecision(1) << calculateArea(*it) << std::endl;
            }
            else if (arg == "VERTEXES") {
                auto compareVertexes = [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                };
                auto it = (cmd == "MAX") 
                    ? std::max_element(polygons.begin(), polygons.end(), compareVertexes)
                    : std::min_element(polygons.begin(), polygons.end(), compareVertexes);
                std::cout << it->points.size() << std::endl;
            }
            else {
                printInvalid();
            }
        }
        else if (cmd == "INTERSECTIONS" || cmd == "LESSAREA" || cmd == "RMECHO" || 
                 cmd == "ECHO" || cmd == "PERMS" || cmd == "MAXSEQ" || 
                 cmd == "INFRAME" || cmd == "SAME" || cmd == "RECTS" || cmd == "RIGHTSHAPES") {
            std::string polygonStr;
            std::getline(iss, polygonStr);
            try {
                Polygon poly = parsePolygon(polygonStr);
                if (cmd == "INTERSECTIONS") {
                    int count = std::count_if(polygons.begin(), polygons.end(),
                        [&poly](const Polygon& p) { return doPolygonsIntersect(poly, p); });
                    std::cout << count << std::endl;
                }
                else if (cmd == "LESSAREA") {
                    double area = calculateArea(poly);
                    int count = std::count_if(polygons.begin(), polygons.end(),
                        [area](const Polygon& p) { return calculateArea(p) < area; });
                    std::cout << count << std::endl;
                }
                else {
                    printInvalid();
                }
            }
            catch (...) {
                printInvalid();
            }
        }
        else {
            printInvalid();
        }
    }
    catch (...) {
        printInvalid();
    }
}
