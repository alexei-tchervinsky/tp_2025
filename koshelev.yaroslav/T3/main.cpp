#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t n;
        if (!(iss >> n) || n < 3) continue;

        Polygon poly;
        poly.points.resize(n);
        bool ok = true;
        for (size_t i = 0; i < n; ++i) {
            if (!(iss >> poly.points[i])) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        iss >> std::ws;
        if (iss.peek() != std::istringstream::traits_type::eof())
            continue;

        polygons.push_back(std::move(poly));
    }

    processCommands(polygons);
    return 0;
}
