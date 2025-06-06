#include "file_io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
bool isValidPolygon(const Polygon& p) {
    if (p.points.size() < 3) return false;
    for (const auto& point : p.points) {
        if (point.x == 0 && point.y == 0) return false;
    }
    return true;
}
vector<Polygon> readPolygonsFromFile(const string& filename) {
    vector<Polygon> polygons;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        try {
            Polygon poly = parsePolygon(line);
            if (isValidPolygon(poly)) {
                polygons.push_back(poly);
            }
        } catch (...) {
        }
    }
    return polygons;
}
Polygon parsePolygon(const string& input) {
    istringstream iss(input);
    int vertexCount;
    if (!(iss >> vertexCount) || vertexCount < 3) {
        throw invalid_argument("Invalid number of vertices");
    }
    Polygon poly;
    for (int i = 0; i < vertexCount; ++i) {
        char c1, c2, c3;
        int x, y;
        if (!(iss >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
            throw invalid_argument("Invalid point format");
        }
        poly.points.push_back({x, y});
    }
    if (poly.points.size() != static_cast<size_t>(vertexCount)) {
        throw invalid_argument("Vertex count mismatch");
    }
    return poly;
}
