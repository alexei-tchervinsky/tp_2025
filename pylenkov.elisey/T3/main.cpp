#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <limits>
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

    return 0;
}
