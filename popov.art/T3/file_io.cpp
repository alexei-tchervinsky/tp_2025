#include "file_io.h"
#include <fstream>
#include <sstream>
#include <iostream>
vector<Polygon> readPolygonsFromFile(const string& filename) {
    vector<Polygon> polygons;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int vertexCount;
        if (!(iss >> vertexCount) || vertexCount < 3) continue;
        Polygon poly;
        bool valid = true;
        for (int i = 0; i < vertexCount && valid; ++i) {
            char c1, c2, c3;
            int x, y;
            if (!(iss >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
                valid = false;
            }
            poly.points.push_back({x, y});
        }
        if (valid && poly.points.size() == static_cast<size_t>(vertexCount)) {
            polygons.push_back(poly);
        }
    }
    return polygons;
}
