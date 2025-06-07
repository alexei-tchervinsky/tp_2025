#include "geometry.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<geom_lab::Polygon> polygons;
    geom_lab::Polygon polygon;

    // Читаем все корректные полигоны из файла, игнорируя некорректные
    while (file >> polygon)
    {
        polygons.push_back(polygon);
    }

    // Очищаем состояние потока и закрываем файл
    file.clear();
    file.close();

    std::map<std::string, std::function<void(std::vector<geom_lab::Polygon>&, std::istream&, std::ostream&)>> commands;

    commands["AREA"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::area(const_polygons, in, out);
    };

    commands["MAX"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::max(const_polygons, in, out);
    };

    commands["MIN"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::min(const_polygons, in, out);
    };

    commands["COUNT"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::count(const_polygons, in, out);
    };

    commands["RIGHTSHAPES"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream&, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::rightshapes(const_polygons, out);
    };

    commands["INFRAME"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::inframe(const_polygons, in, out);
    };

    commands["LESSAREA"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::lessarea(const_polygons, in, out);
    };

    commands["MAXSEQ"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        const std::vector<geom_lab::Polygon>& const_polygons = polygons;
        geom_lab::maxseq(const_polygons, in, out);
    };

    commands["ECHO"] = [](std::vector<geom_lab::Polygon>& polygons, std::istream& in, std::ostream& out) {
        geom_lab::echo(polygons, in, out);
    };

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        try
        {
            auto it = commands.find(command);
            if (it != commands.end())
            {
                it->second(polygons, iss, std::cout);
                std::cout << std::endl;
            }
            else
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        catch (const std::exception&)
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    return 0;
}
