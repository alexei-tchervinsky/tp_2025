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
#ifdef ALEXEIT

    std::vector<Polygon> polygons;

    while(!file.eof())
    {
#endif // ALEXEIT
#ifndef ALEXEIT
        std::vector<Polygon> polygons;
#endif // !ALEXEIT
        std::copy(std::istream_iterator<Polygon>(file),
                std::istream_iterator<Polygon>(),
                std::back_inserter(polygons));
#ifdef ALEXEIT
        if (!file.fail())
        {
            continue;
        }
        file.clear();  // Очищаем состояние ошибки
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем оставшийся ввод
    }
#endif // ALEXEIT

    if (polygons.empty())
    {
        LOG("Warning: No polygons loaded from file\n")
    }

    std::map<std::string, CommandHandler> commands;

    commands["AREA"] = [](const std::vector<Polygon>& polygons) {
        std::string param;
        std::cin >> param;
        area(polygons, param);
    };

    commands["MAX"] = [](const std::vector<Polygon>& polygons) {
        std::string param;
        std::cin >> param;
        max(polygons, param);
    };

    commands["MIN"] = [](const std::vector<Polygon>& polygons) {
        std::string param;
        std::cin >> param;
        min(polygons, param);
    };

    commands["COUNT"] = [](const std::vector<Polygon>& polygons) {
        std::string param;
        std::cin >> param;
        count(polygons, param);
    };

    commands["ECHO"] = [&polygons, argv](const std::vector<Polygon>&) {
        Polygon target;
        std::cin >> target;
        echo(polygons, target, argv[1]);
    };

    commands["MAXSEQ"] = [](const std::vector<Polygon>& polygons) {
        Polygon target;
        std::cin >> target;
#ifdef ALEXEIT
        if (std::cin.fail())
        {
#if 1
            std::cin.clear();  // Очищаем состояние ошибки
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем оставшийся ввод
            std::cout << INV_CMD;
            return;
        }
#endif
            // throw std::invalid_argument(INV_CMD);
            // throw std::invalid_argument("<INVALID COMMAND>");
#else
                    throw std::invalid_argument("<INVALID COMMAND>");
        }
#endif // ALEXEIT
        maxSeq(polygons, target);
    };

    std::string cmd;
    while (std::cin >> cmd)
    {
        LOG(cmd)
        try
        {
            auto it = commands.find(cmd);
            if (it != commands.end())
            {
                it->second(polygons);
            }
            else
            {
                throw std::invalid_argument("<INVALID COMMAND 0>");
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

#if 0
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

                LOG("MAXSEQ")
                Polygon target;
                std::cin >> target;

                if (std::cin.fail())
                {
#ifdef ALEXEIT
#if 1
                std::cin.clear();  // Очищаем состояние ошибки
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем оставшийся ввод
                std::cout << INV_CMD;
                continue;
#endif
                throw std::invalid_argument(INV_CMD);
#else
                    throw std::invalid_argument("<INVALID COMMAND>");
#endif // ALEXEIT
                }

                maxSeq(polygons, target);
            }
            else
            {
                throw std::invalid_argument(INV_CMD);
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what();  // Выводим ошибку один раз
            std::cin.clear();  // Очищаем состояние ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем оставшийся ввод
        }
        catch (const std::logic_error& e)
        {
            std::cout << e.what();  // Выводим ошибку один раз
            std::cin.clear();  // Очищаем состояние ошибки
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем оставшийся ввод
        }
    }
#endif
    return 0;
}
