#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>
#include <sstream>

namespace prokopenko {

  double getArea(const Polygon& p) {
    double area = 0.0;
    for (size_t i = 0; i < p.points.size(); ++i) {
      const Point& a = p.points[i];
      const Point& b = p.points[(i + 1) % p.points.size()];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }

  bool parsePolygon(const std::string& line, Polygon& poly) {
    std::istringstream iss(line);
    std::string dummy;
    int count;
    if (!(iss >> dummy >> count)) return false;
    if (count < 3) return false;

    Polygon p;
    for (int i = 0; i < count; ++i) {
      char ch;
      Point pt;
      if (!(iss >> ch) || ch != '(') return false;
      if (!(iss >> pt.x)) return false;
      if (!(iss >> ch) || ch != ';') return false;
      if (!(iss >> pt.y)) return false;
      if (!(iss >> ch) || ch != ')') return false;
      p.points.push_back(pt);
    }
    if (p.points.size() != static_cast<size_t>(count)) return false;
    poly = p;
    return true;
  }

  void doCommand(const std::string& cmd, std::vector<Polygon>& polygons, std::istream& in) {
    if (cmd == "COUNT") {
      std::string arg;
      if (!(in >> arg)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }

      if (arg == "EVEN" || arg == "ODD") {
        int parity = (arg == "EVEN") ? 0 : 1;
        int count = std::count_if(polygons.begin(), polygons.end(), [parity](const Polygon& p) {
          return p.points.size() % 2 == parity;
          });
        std::cout << count << '\n';
      }
      else {
        try {
          int n = std::stoi(arg);
          int count = std::count_if(polygons.begin(), polygons.end(), [n](const Polygon& p) {
            return p.points.size() == static_cast<size_t>(n);
            });
          std::cout << count << '\n';
        }
        catch (...) {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "AREA") {
      std::string arg;
      if (!(in >> arg)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }

      if (arg == "EVEN" || arg == "ODD") {
        int parity = (arg == "EVEN") ? 0 : 1;
        double total = 0.0;
        for (const auto& p : polygons) {
          if (p.points.size() % 2 == parity) {
            total += getArea(p);
          }
        }
        std::cout << std::fixed << std::setprecision(1) << total << '\n';
      }
      else {
        try {
          int n = std::stoi(arg);
          double total = 0.0;
          for (const auto& p : polygons) {
            if (p.points.size() == static_cast<size_t>(n)) {
              total += getArea(p);
            }
          }
          std::cout << std::fixed << std::setprecision(1) << total << '\n';
        }
        catch (...) {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "ECHO") {
      std::string line;
      std::getline(in, line);
      if (line.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      Polygon p;
      if (parsePolygon("ECHO" + line, p)) {
        if (p.points.size() >= 3) {
          polygons.push_back(p);
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

}
