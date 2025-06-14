#include "Geometry.h"
#include "Commands.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    try
    {
        std::vector<kuzminykh::Polygon> polygons = kuzminykh::readFile(argv[1]);
        const auto commands = kuzminykh::createCommandMap();

        std::string line;
        while (std::getline(std::cin, line))
        {
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd;

            if (cmd.empty()) continue;

            auto it = commands.find(cmd);
            if (it != commands.end())
            {
                try
                {
                    it->second(polygons, ss);
                }
                catch (...)
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }
            else
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
