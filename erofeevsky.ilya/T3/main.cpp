#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <limits>
#include <vector>
#include "geometry.hpp"
#include "iofmtguard.hpp"

int main(int argc, char* argv[])
{
  using namespace ilyaerofick;

  // Проверка аргументов командной строки
  if (argc != 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }

  // Чтение полигонов из файла
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "File not open\n";
    return 1;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;

  while (!in.eof())
  {
    std::copy(input_it_t{ in }, input_it_t{}, std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  in.close();

  // Настройка команд
 std::map< std::string,
         std::function< void(std::istream&, std::ostream&) > > commands;
{
    using namespace std::placeholders;
    commands["AREA"] = std::bind(areaCommand, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(countCommand, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(maxCommand, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(minCommand, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmEchoCommand, std::ref(polygons), _1, _2);
    commands["INFRAME"] = std::bind(inframeCommand, std::cref(polygons), _1, _2);
    commands["RIGHTSHAPES"] = std::bind(rightshapesCommand, std::cref(polygons), _2);
}

  // Обработка команд пользователя
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << "\n";
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}