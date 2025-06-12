#include "Commands.hpp"
#include "parser.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

void executeCommand(const std::string& line, std::vector<Polygon>& polygons) {
  std::istringstream iss(line);
  std::string cmd;
  iss >> cmd;

  if (cmd == "ADD") {
    Polygon p = parsePolygon(line.substr(4));
    polygons.push_back(p);
  }
  else if (cmd == "PRINT") {
    for (const auto& p : polygons) {
      p.print();
    }
  }
  else if (cmd == "PERIMETER") {
    double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double sum, const Polygon& p) {
        return sum + p.perimeter();
      });
    std::cout << "Total perimeter: " << total << std::endl;
  }
  else if (cmd == "COUNT") {
    std::cout << "Total polygons: " << polygons.size() << std::endl;
  }
  else if (cmd == "VERTEXES") {
    size_t total = std::accumulate(polygons.begin(), polygons.end(), 0,
      [](size_t sum, const Polygon& p) {
        return sum + p.vertexCount();
      });
    std::cout << "Total vertexes: " << total << std::endl;
  }
  else if (cmd == "ECHO") {
    std::string args;
    std::getline(iss, args);
    Polygon p = parsePolygon(args);
    size_t inserted = 0;
    for (size_t i = 0; i < polygons.size(); ++i) {
      if (polygons[i] == p) {
        polygons.insert(polygons.begin() + i + 1, p);
        ++i;
        ++inserted;
      }
    }
    std::cout << "Inserted " << inserted << " copies." << std::endl;
  }
  else if (cmd == "EXIT") {
    exit(0);
  }
  else {
    std::cerr << "Unknown command: " << cmd << std::endl;
  }
}
