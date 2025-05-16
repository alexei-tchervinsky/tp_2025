#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "DataStruct.hpp"
#include "commands.hpp"
#include "iofmtguard.hpp"

using namespace nspace;

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Error: Cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::copy(std::istream_iterator<Polygon>(file),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));

    std::string cmd;
    while (std::cin >> cmd)
    {
        try
        {
            if (cmd == "AREA")
            {
                std::string param;
                std::cin >> param;
                area(polygons, param);
            }
            else if (cmd == "MAX")
            {
                std::string param;
                std::cin >> param;
                max(polygons, param);
            }
            else if (cmd == "MIN")
            {
                std::string param;
                std::cin >> param;
                min(polygons, param);
            }
            else if (cmd == "COUNT")
            {
                std::string param;
                std::cin >> param;
                count(polygons, param);
            }
            else if (cmd == "ECHO")
            {
                Polygon target;
                std::cin >> target;
                echo(polygons, target, argv[1]);
            }
            else if (cmd == "MAXSEQ")
            {
                Polygon target;
                std::cin >> target;
                maxSeq(polygons, target);
            }
            else
            {
                throw std::invalid_argument("");
            }
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}