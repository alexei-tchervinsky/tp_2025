#include "readfile.hpp"

namespace tarasov {

Polygon parsePolygon(const std::string& str) {
    std::istringstream ss(str);
    Polygon p;
    size_t number_of_vertices;
    ss >> number_of_vertices;

    if (ss.fail() || number_of_vertices < 3) {
        throw std::runtime_error("Неправильный ввод");
    }
    p.points.resize(number_of_vertices);
    for (size_t i = 0; i < number_of_vertices; ++i) {
        if (!(ss >> p.points[i])) {
            throw std::runtime_error("Неверные координаты");
        }
    }

    std::string remaining;
    if (ss >> remaining && !remaining.empty()) {
        throw std::runtime_error("Большое количество точек");
    }
    return p;
}


std::vector<Polygon> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Нельзя открыть файл: " << fileName << std::endl;
        exit(1);
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || std::ranges::all_of(line, [](unsigned char c){ return std::isspace(c);})) {
            continue;
        }

        try {
            Polygon p = tarasov::parsePolygon(line);
            polygons.push_back(p);
        } catch (const std::runtime_error& e) {}
    }
    file.close();
    return polygons;
}
}
