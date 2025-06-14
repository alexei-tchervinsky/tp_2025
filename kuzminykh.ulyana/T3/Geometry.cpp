#include "Geometry.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace kuzminykh
{
    bool Point::operator<(const Point& other) const
    {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }

    bool Point::operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    std::istream& operator>>(std::istream& in, Point& p)
    {
        char dummy;
        in >> dummy >> p.x >> dummy >> p.y >> dummy;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "(" << p.x << ";" << p.y << ")";
        return out;
    }

    Polygon parsePolygon(const std::string& str)
    {
        std::istringstream ss(str);
        Polygon p;
        size_t vertexCount;
        ss >> vertexCount;

        if (ss.fail() || vertexCount < 3)
            throw std::runtime_error("Invalid polygon");

        p.points.resize(vertexCount);
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(ss >> p.points[i]))
                throw std::runtime_error("Invalid point");
        }

        std::string remaining;
        if (ss >> remaining && !remaining.empty())
            throw std::runtime_error("Extra data");

        return p;
    }

    std::vector<Polygon> readFile(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            std::cerr << "Can't open file: " << fileName << std::endl;
            exit(1);
        }

        std::vector<Polygon> polygons;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || std::all_of(line.begin(), line.end(),
                [](unsigned char c) { return std::isspace(c); }))
                continue;

            try
            {
                polygons.push_back(parsePolygon(line));
            }
            catch (...) {}
        }

        return polygons;
    }
}
