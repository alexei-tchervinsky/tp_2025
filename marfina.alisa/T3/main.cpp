#include "geometry.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        return 1;
    }
    try
    {
        std::vector<Polygon> polygons = readPolygonsFromFile(argv[1]);
        processCommands(polygons);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
