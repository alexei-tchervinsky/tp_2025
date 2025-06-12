#include "commands.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <numeric>

namespace prokopenko {

  void executeCommand(const std::string& line, std::vector<Polygon>& polygons) {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    std::cout << std::fixed << std::setprecision(1);

    if (command == "AREA") {
      std::string arg;
      iss >> arg;
      if (arg == "EVEN" || arg == "ODD") {
        bool even = (arg == "EVEN");
        auto predicate = [even](const Polygon& p) {
          return (p.points.size() % 2 == 0) == even;
          };
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
          [predicate](double acc, const Polygon& p) {
            return predicate(p) ? acc + computeArea(p) : acc;
          });
        std::cout << sum << '\n';
      }
      else if (arg == "MEAN") {
        if (polygons.empty()) {
          std::cout << "<INVALID COMMAND>\n";
          return;
        }
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
          [](double acc, const Polygon& p) {
            return acc + computeArea(p);
          });
        std::cout << sum / polygons.size() << '\n';
      }
      else {
        try {
          int n = std::stoi(arg);
          double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [n](double acc, const Polygon& p) {
              return p.points.size() == static_cast<size_t>(n)
                ? acc + computeArea(p)
                : acc;
            });
          std::cout << sum << '\n';
        }
        catch (...) {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "MAX" || command == "MIN") {
      std::string arg;
      iss >> arg;
      if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      if (arg == "AREA") {
        auto areaFunc = [](const Polygon& p) { return computeArea(p); };
        auto it = (command == "MAX")
          ? std::max_element(polygons.begin(), polygons.end(),
            [&](const Polygon& a, const Polygon& b) {
              return areaFunc(a) < areaFunc(b);
            })
          : std::min_element(polygons.begin(), polygons.end(),
            [&](const Polygon& a, const Polygon& b) {
              return areaFunc(a) < areaFunc(b);
            });
        std::cout << computeArea(*it) << '\n';
      }
      else if (arg == "VERTEXES") {
        auto it = (command == "MAX")
          ? std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.points.size() < b.points.size();
            })
          : std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
              return a.points.size() < b.points.size();
            });
        std::cout << it->points.size() << '\n';
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "COUNT") {
      std::string arg;
      iss >> arg;
      size_t count = 0;
      if (arg == "EVEN" || arg == "ODD") {
        bool even = (arg == "EVEN");
        count = std::count_if(polygons.begin(), polygons.end(),
          [even](const Polygon& p) {
            return (p.points.size() % 2 == 0) == even;
          });
      }
      else {
        try {
          int n = std::stoi(arg);
          count = std::count_if(polygons.begin(), polygons.end(),
            [n](const Polygon& p) {
              return static_cast<int>(p.points.size()) == n;
            });
        }
        catch (...) {
          std::cout << "<INVALID COMMAND>\n";
          return;
        }
      }
      std::cout << count << '\n';
    }
    else if (command == "RIGHTSHAPES") {
      size_t count = std::count_if(polygons.begin(), polygons.end(),
        [](const Polygon& p) {
          return hasRightAngle(p);
        });
      std::cout << count << '\n';
    }
    else if (command == "ECHO") {
      std::string rest;
      std::getline(iss, rest);
      Polygon p = parsePolygon(rest);
      if (p.points.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      size_t inserted = 0;
      for (size_t i = 0; i < polygons.size(); ++i) {
        if (polygons[i] == p) {
          polygons.insert(polygons.begin() + i + 1, p);
          ++i;
          ++inserted;
        }
      }
      std::cout << inserted << '\n';
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

} // namespace prokopenko
