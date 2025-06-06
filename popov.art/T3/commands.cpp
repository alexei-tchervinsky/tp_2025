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
namespace {
    bool isValidPolygon(const Polygon& p) {
        if (p.points.size() < 3) return false;
        for (size_t i = 1; i < p.points.size(); ++i) {
            if (p.points[i] == p.points[i-1]) {
                return false;
            }
        }
        return true;
    }
    void printInvalid() { cout << "<INVALID COMMAND>" << endl; }
    template <typename Predicate>
    int countIfValid(const vector<Polygon>& polygons, Predicate pred) {
        return count_if(polygons.begin(), polygons.end(),
            [&pred](const Polygon& p) {
                return isValidPolygon(p) && pred(p);
            });
    }
    template <typename Predicate>
    double accumulateIfValid(const vector<Polygon>& polygons, Predicate pred) {
        return accumulate(polygons.begin(), polygons.end(), 0.0,
            [&pred](double acc, const Polygon& p) {
                return isValidPolygon(p) ? acc + pred(p) : acc;
            });
    }
}
void processCommand(const string& command, vector<Polygon>& polygons) {
    istringstream iss(command);
    string cmd;
    if (!(iss >> cmd)) {
        printInvalid();
        return;
    }
    try {
        if (cmd == "COUNT") {
            string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            if (arg == "EVEN") {
                cout << countIfValid(polygons, [](const Polygon& p) { 
                    return p.points.size() % 2 == 0; 
                }) << endl;
            }
            else if (arg == "ODD") {
                cout << countIfValid(polygons, [](const Polygon& p) { 
                    return p.points.size() % 2 != 0; 
                }) << endl;
            }
            else {
                int num = stoi(arg);
                if (num < 3) throw invalid_argument("Invalid vertex count");
                cout << countIfValid(polygons, [num](const Polygon& p) { 
                    return p.points.size() == static_cast<size_t>(num); 
                }) << endl;
            }
        }
        else if (cmd == "INTERSECTIONS" || cmd == "LESSAREA") {
            string polygonStr;
            getline(iss >> ws, polygonStr);
            Polygon poly = parsePolygon(polygonStr);
            if (!isValidPolygon(poly)) throw invalid_argument("Invalid polygon");
            if (cmd == "INTERSECTIONS") {
                cout << countIfValid(polygons, [&poly](const Polygon& p) {
                    return doPolygonsIntersect(poly, p);
                }) << endl;
            }
            else {
                double area = calculateArea(poly);
                cout << countIfValid(polygons, [area](const Polygon& p) {
                    return calculateArea(p) < area;
                }) << endl;
            }
        }
        else if (cmd == "AREA") {
            string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            iofmtguard guard(cout);
            cout << fixed << setprecision(1);

            if (arg == "EVEN") {
                cout << accumulateIfValid(polygons, [](const Polygon& p) {
                    return p.points.size() % 2 == 0 ? calculateArea(p) : 0.0;
                }) << endl;
            }
            else if (arg == "ODD") {
                cout << accumulateIfValid(polygons, [](const Polygon& p) {
                    return p.points.size() % 2 != 0 ? calculateArea(p) : 0.0;
                }) << endl;
            }
            else if (arg == "MEAN") {
                size_t validCount = count_if(polygons.begin(), polygons.end(), isValidPolygon);
                if (validCount == 0) throw logic_error("No valid polygons");
                cout << accumulateIfValid(polygons, [](const Polygon& p) {
                    return calculateArea(p);
                }) / validCount << endl;
            }
            else {
                int num = stoi(arg);
                if (num < 3) throw invalid_argument("Invalid vertex count");
                cout << accumulateIfValid(polygons, [num](const Polygon& p) {
                    return p.points.size() == static_cast<size_t>(num) ? calculateArea(p) : 0.0;
                }) << endl;
            }
        }
        else if (cmd == "MAX" || cmd == "MIN") {
            vector<Polygon> validPolygons;
            copy_if(polygons.begin(), polygons.end(), back_inserter(validPolygons), isValidPolygon);
            
            if (validPolygons.empty()) throw logic_error("No valid polygons");
            string arg;
            if (!(iss >> arg)) {
                printInvalid();
                return;
            }
            if (arg == "AREA") {
                iofmtguard guard(cout);
                cout << fixed << setprecision(1);
                auto compare = [](const Polygon& a, const Polygon& b) {
                    return calculateArea(a) < calculateArea(b);
                };
                auto it = (cmd == "MAX")
                    ? max_element(validPolygons.begin(), validPolygons.end(), compare)
                    : min_element(validPolygons.begin(), validPolygons.end(), compare);
                cout << calculateArea(*it) << endl;
            }
            else if (arg == "VERTEXES") {
                auto compare = [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                };
                auto it = (cmd == "MAX")
                    ? max_element(validPolygons.begin(), validPolygons.end(), compare)
                    : min_element(validPolygons.begin(), validPolygons.end(), compare);
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
    catch (...) {
        printInvalid();
    }
}
