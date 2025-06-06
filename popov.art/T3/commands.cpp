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
using namespace std;
void processCommand(const string& command, vector<Polygon>& polygons) {
    istringstream iss(command);
    string cmd;
    if (!(iss >> cmd)) {
        cout << "<INVALID COMMAND>" << endl;
        return;
    }
    auto printInvalid = []() { cout << "<INVALID COMMAND>" << endl; };
    if (cmd == "COUNT") {
        string arg;
        if (!(iss >> arg)) {
            printInvalid();
            return;
        }
        auto isValidPolygon = [](const Polygon& p) { return p.points.size() >= 3; };
        if (arg == "EVEN") {
            int count = count_if(polygons.begin(), polygons.end(),
                [&](const Polygon& p) {
                    return isValidPolygon(p) && p.points.size() % 2 == 0;
                });
            cout << count << endl;
        }
        else if (arg == "ODD") {
            int count = count_if(polygons.begin(), polygons.end(),
                [&](const Polygon& p) {
                    return isValidPolygon(p) && p.points.size() % 2 != 0;
                });
            cout << count << endl;
        }
        else {
            try {
                int num = stoi(arg);
                if (num < 3) throw invalid_argument("Invalid vertex count");
                int count = count_if(polygons.begin(), polygons.end(),
                    [&](const Polygon& p) {
                        return isValidPolygon(p) && p.points.size() == static_cast<size_t>(num);
                    });
                cout << count << endl;
            }
            catch (...) {
                printInvalid();
            }
        }
    }
    else if (cmd == "INTERSECTIONS" || cmd == "LESSAREA") {
        string polygonStr;
        getline(iss, polygonStr);
        size_t openParen = count(polygonStr.begin(), polygonStr.end(), '(');
        size_t closeParen = count(polygonStr.begin(), polygonStr.end(), ')');
        size_t semicolons = count(polygonStr.begin(), polygonStr.end(), ';');
        if (openParen < 3 || openParen != closeParen || semicolons < openParen) {
            printInvalid();
            return;
        }
        try {
            Polygon poly = parsePolygon(polygonStr);
            if (poly.points.size() < 3) throw invalid_argument("Invalid polygon");
            if (cmd == "INTERSECTIONS") {
                int count = count_if(polygons.begin(), polygons.end(),
                    [&](const Polygon& p) {
                        return p.points.size() >= 3 && doPolygonsIntersect(poly, p);
                    });
                cout << count << endl;
            }
            else { // LESSAREA
                double area = calculateArea(poly);
                int count = count_if(polygons.begin(), polygons.end(),
                    [&](const Polygon& p) {
                        return p.points.size() >= 3 && calculateArea(p) < area;
                    });
                cout << count << endl;
            }
        }
        catch (...) {
            printInvalid();
        }
    }
    else if (cmd == "AREA") {
        string arg;
        if (!(iss >> arg)) {
            printInvalid();
            return;
        }
        if (arg == "EVEN") {
            double sum = accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) {
                    return p.points.size() >= 3 && p.points.size() % 2 == 0 ? acc + calculateArea(p) : acc;
                });
            cout << fixed << setprecision(1) << sum << endl;
        }
        else if (arg == "ODD") {
            double sum = accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) {
                    return p.points.size() >= 3 && p.points.size() % 2 != 0 ? acc + calculateArea(p) : acc;
                });
            cout << fixed << setprecision(1) << sum << endl;
        }
        else if (arg == "MEAN") {
            if (polygons.empty()) {
                printInvalid();
                return;
            }
            double sum = accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) {
                    return p.points.size() >= 3 ? acc + calculateArea(p) : acc;
                });
            cout << fixed << setprecision(1) << sum / polygons.size() << endl;
        }
        else {
            try {
                int num = stoi(arg);
                if (num < 3) throw invalid_argument("Invalid vertex count");
                double sum = accumulate(polygons.begin(), polygons.end(), 0.0,
                    [num](double acc, const Polygon& p) {
                        return p.points.size() == static_cast<size_t>(num) ? acc + calculateArea(p) : acc;
                    });
                cout << fixed << setprecision(1) << sum << endl;
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
        string arg;
        if (!(iss >> arg)) {
            printInvalid();
            return;
        }
        if (arg == "AREA") {
            auto valid_end = remove_if(polygons.begin(), polygons.end(),
                [](const Polygon& p) { return p.points.size() < 3; });
            if (polygons.begin() == valid_end) {
                printInvalid();
                return;
            }
            auto compareArea = [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            };
            auto it = (cmd == "MAX")
                ? max_element(polygons.begin(), valid_end, compareArea)
                : min_element(polygons.begin(), valid_end, compareArea);
            cout << fixed << setprecision(1) << calculateArea(*it) << endl;
        }
        else if (arg == "VERTEXES") {
            auto valid_end = remove_if(polygons.begin(), polygons.end(),
                [](const Polygon& p) { return p.points.size() < 3; });
            if (polygons.begin() == valid_end) {
                printInvalid();
                return;
            }
            auto compareVertexes = [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            };
            auto it = (cmd == "MAX")
                ? max_element(polygons.begin(), valid_end, compareVertexes)
                : min_element(polygons.begin(), valid_end, compareVertexes);
            cout << it->points.size() << endl;
        }
        else {
            printInvalid();
        }
    }
    else {
        printInvalid();
    }
}
