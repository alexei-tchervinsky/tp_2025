#include "commands.h"
#include "polygon_operations.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iostream>

void processCommand(const std::string& command, std::vector<Polygon>& polygons) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    
    if (cmd == "AREA") {
        std::string arg;
        iss >> arg;
        
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
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) { return acc + calculateArea(p); });
            std::cout << std::fixed << std::setprecision(1) << sum / polygons.size() << std::endl;
        }
        else {
            try {
                int num = std::stoi(arg);
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [num](double acc, const Polygon& p) {
                        return acc + (p.points.size() == num ? calculateArea(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            }
            catch (...) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }
    else if (cmd == "MAX") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        
        std::string arg;
        iss >> arg;
        
        if (arg == "AREA") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return calculateArea(a) < calculateArea(b);
                });
            std::cout << std::fixed << std::setprecision(1) << calculateArea(*it) << std::endl;
        }
        else if (arg == "VERTEXES") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            std::cout << it->points.size() << std::endl;
        }
        else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    else if (cmd == "MIN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        
        std::string arg;
        iss >> arg;
        
        if (arg == "AREA") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return calculateArea(a) < calculateArea(b);
                });
            std::cout << std::fixed << std::setprecision(1) << calculateArea(*it) << std::endl;
        }
        else if (arg == "VERTEXES") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            std::cout << it->points.size() << std::endl;
        }
        else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    else if (cmd == "COUNT") {
        std::string arg;
        iss >> arg;
        
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
                int count = std::count_if(polygons.begin(), polygons.end(),
                    [num](const Polygon& p) { return p.points.size() == num; });
                std::cout << count << std::endl;
            }
            catch (...) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }
    else if (cmd == "LESSAREA") {
        std::string polygonStr;
        std::getline(iss, polygonStr);
        try {
            Polygon poly = parsePolygon(polygonStr);
            double area = calculateArea(poly);
            int count = std::count_if(polygons.begin(), polygons.end(),
                [area](const Polygon& p) { return calculateArea(p) < area; });
            std::cout << count << std::endl;
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    else if (cmd == "INTERSECTIONS") {
        std::string polygonStr;
        std::getline(iss, polygonStr);
        try {
            Polygon poly = parsePolygon(polygonStr);
            int count = std::count_if(polygons.begin(), polygons.end(),
                [&poly](const Polygon& p) { return doPolygonsIntersect(poly, p); });
            std::cout << count << std::endl;
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}
