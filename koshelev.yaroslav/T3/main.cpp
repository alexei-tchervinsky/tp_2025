#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "polygon.h"
#include "commands.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open file " << argv[1] << '\n';
        return 1;
    }

    std::vector<Polygon> polygons;
    for (Polygon poly; file >> poly; ) {
        if (poly.vertexCount() >= 3) {
            polygons.push_back(std::move(poly));
        }
    }

    processCommands(polygons);
    return 0;
}