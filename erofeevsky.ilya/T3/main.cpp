#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <limits>
#include "geometry.hpp"
#include "iofmtguard.hpp"

int main(int argc, char* argv[])
{
  using namespace erofick;
  //проверка аргументов командной строки
  if (argc != 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }

  //открытие файла
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "File not open\n";
    return 1;
  }
  //чтение из файла
  using input_it_t = std::istream_iterator< Polygon >;
  std::vector< Polygon > value;
  while (!in.eof())
  {
    std::copy(input_it_t{ in }, input_it_t{}, std::back_inserter(value));
    if (in.fail()) //если ошибка чтения
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  in.close();
  //настройка команд
  std::map< std::string, std::function< void(std::istream&,
     std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    //привязываем функции к командам
    commands["AREA"] = std::bind(area, std::cref(value), _1, _2);
    commands["COUNT"] = std::bind(count, std::cref(value), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(value), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(value), _1, _2);
    commands["INFRAME"] = std::bind(inframe, std::cref(value), _1, _2);
    commands["RMECHO"] = std::bind(rmecho, std::ref(value), _1, _2);
  }
  //обработка команд пользователя
  std::string cmd = "";
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout); //выполняем команду
      std::cout << "\n";
    }
    catch (...) //обработка ошибок
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    //очистка состояния потока
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
