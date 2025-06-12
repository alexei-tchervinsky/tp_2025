#include "Commands.hpp"
#include "Polygon.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>

namespace prokopenko {

  void doCommand(const std::string& command, std::vector<Polygon>& data, std::istream& in) {
    std::ios_base::fmtflags f(std::cout.flags());
    std::streamsize prec = std::cout.precision();

    if (command == "ECHO") {
      Polygon p;
      if (in >> p) {
        data.push_back(p);
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    else if (command == "COUNT ODD" || command == "COUNT EVEN") {
      int parity = (command == "COUNT ODD") ? 1 : 0;
      int count = std::count_if(data.begin(), data.end(), [parity](const Polygon& p) {
        return (static_cast<int>(p.points.size()) % 2) == parity;
        });
      std::cout << count << '\n';
    }
    else if (command == "AREA ODD" || command == "AREA EVEN") {
      int parity = (command == "AREA ODD") ? 1 : 0;
      double total = 0.0;
      for (const Polygon& p : data) {
        if (static_cast<int>(p.points.size()) % 2 == parity) {
          total += getArea(p);
        }
      }
      std::cout << std::fixed << std::setprecision(1) << total << '\n';
    }
    else if (command.rfind("COUNT", 0) == 0) {
      int n;
      std::string rest;
      std::getline(in, rest);
      std::istringstream iss(rest);
      if (iss >> n) {
        int count = std::count_if(data.begin(), data.end(), [n](const Polygon& p) {
          return static_cast<int>(p.points.size()) == n;
          });
        std::cout << count << '\n';
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command.rfind("AREA", 0) == 0) {
      std::cout << "<INVALID COMMAND>\n";
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }

    std::cout.flags(f);
    std::cout.precision(prec);
  }

}
