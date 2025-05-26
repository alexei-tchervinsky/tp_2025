#include "file_io.h"
#include <fstream>
std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int vertexCount;
        if (!(iss >> vertexCount)) continue;
        Polygon poly;
        bool valid = true;
        for (int i = 0; i < vertexCount; ++i) {
            char c1, c2, c3;
            int x, y;
            if (!(iss >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
                valid = false;
                break;
            }
            poly.points.push_back({x, y});
        }
        if (valid && poly.points.size() == static_cast<size_t>(vertexCount)) {
            polygons.push_back(poly);
        }
    }
    return polygons;
}
