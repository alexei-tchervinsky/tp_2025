#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <limits>
#include <map>
#include <functional>
#include "DataStruct.hpp"
#include "commands.hpp"
#include "iofmtguard.hpp"

using namespace nspace;

using CommandHandler = std::function<void(const std::vector<Polygon>&)>;

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

    while(!file.eof())
    {
        std::copy(std::istream_iterator<Polygon>(file),
                std::istream_iterator<Polygon>(),
                std::back_inserter(polygons));
        if (!file.fail())
        {
            continue;
        }
        file.clear();
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::map<std::string, CommandHandler> commands;

    commands["AREA"] = [](const std::vector<Polygon>& polygons)
    {
        std::string param;
        std::cin >> param;
        area(polygons, param);
    };

    commands["MAX"] = [](const std::vector<Polygon>& polygons)
    {
        std::string param;
        std::cin >> param;
        max(polygons, param);
    };

    commands["MIN"] = [](const std::vector<Polygon>& polygons)
    {
        std::string param;
        std::cin >> param;
        max(polygons, param);
    };

    commands["COUNT"] = [](const std::vector<Polygon>& polygons)
    {
        std::string param;
        std::cin >> param;
        count(polygons, param);
    };

    commands["ECHO"] = [&polygons, argv](const std::vector<Polygon>&)
    {
        Polygon target;
        std::cin >> target;
        echo(polygons, target, argv[1]);
    };

    commands["MAXSEQ"] = [](const std::vector<Polygon>& polygons)
    {
        Polygon target;
        std::cin >> target;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "<INVALID COMMAND>\n";
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        maxSeq(polygons, target);
    };


    std::string cmd;
    while (std::cin >> cmd)
    {
        try
        {
            auto it = commands.find(cmd);
            if (it != commands.end())
            {
                it -> second(polygons);
            }
            else
            {
                throw std::invalid_argument("<INVALID COMMAND>\n");
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what();  // Выводим ошибку один раз
            std::cin.clear();  // Очищаем состояние ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::logic_error& e)
        {
            std::cout << e.what() << std::endl;  // Выводим ошибку один раз
            std::cin.clear();  // Очищаем состояние ошибки
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
