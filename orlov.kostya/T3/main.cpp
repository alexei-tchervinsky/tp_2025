#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <sstream>

#include "datastruct.hpp"
#include "commands.hpp"

using orlov::Polygon;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "ERROR: filename not specified" << std::endl;
        return 1;
    }
    const std::string filename = argv[1];
    std::ifstream fileIn(filename);

    if (!fileIn)
    {
        std::cerr << "ERROR: cannot open file " << filename << std::endl;
        return 1;
    }

    std::vector<orlov::Polygon> polygons;
    while (fileIn.peek() != EOF)
    {
        std::copy
        (
            std::istream_iterator<Polygon>(fileIn),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygons)
        );

        if(fileIn.fail()) fileIn.clear();
    }

    fileIn.close();

    while(std::cin.peek() != EOF)
    {
        std::string line;
        if(!std::getline(std::cin, line)) break;

        std::istringstream commandIn(line);
        orlov::executeCommand(polygons, commandIn, std::cout);

        if(commandIn.fail())
            std::cout << "<INVALID COMMAND>";

        std::cout << std::endl;
    }
    return 0;
}

