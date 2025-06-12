#include "polygon.hpp"
#include <iostream>
#include <sstream>

using namespace prokopenko;

void processPolygonCommands() {
  Polygon poly;
  std::string line;
  std::cout << "Enter commands (ADD x y | AREA | PERIMETER | PRINT | EXIT):\n";

  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "ADD") {
      double x, y;
      iss >> x >> y;
      poly.addPoint(Point{ x, y });
    }
    else if (command == "AREA") {
      std::cout << "Area: " << poly.area() << "\n";
    }
    else if (command == "PERIMETER") {
      std::cout << "Perimeter: " << poly.perimeter() << "\n";
    }
    else if (command == "PRINT") {
      std::cout << poly.toString() << "\n";
    }
    else if (command == "EXIT") {
      break;
    }
    else {
      std::cout << "Unknown command.\n";
    }
  }
}
