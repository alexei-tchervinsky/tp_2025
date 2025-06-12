#include "Commands.hpp"
#include "Polygon.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>

namespace prokopenko {

  using namespace std;

  void doCommand(const std::string& command, std::vector<Polygon>& data, std::istream& in) {
    if (command == "ECHO") {
      Polygon p;
      in >> p;
      data.push_back(p);
    }
    else if (command == "COUNT") {
      int n;
      in >> n;
      int count = std::count_if(data.begin(), data.end(), [n](const Polygon& p) {
        return static_cast<int>(p.points.size()) == n;
        });
      std::cout << count << '\n';
    }
    else if (command == "COUNT ODD" || command == "COUNT EVEN") {
      int parity = (command == "COUNT ODD") ? 1 : 0;
      int count = std::count_if(data.begin(), data.end(), [parity](const Polygon& p) {
        return static_cast<int>(p.points.size()) % 2 == parity;
        });
      std::cout << count << '\n';
    }
    else if (command == "AREA ODD" || command == "AREA EVEN") {
      int parity = (command == "AREA ODD") ? 1 : 0;
      double sum = 0.0;
      for (const Polygon& p : data) {
        if (static_cast<int>(p.points.size()) % 2 == parity) {
          sum += getArea(p);
        }
      }
      std::cout << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (command.rfind("AREA", 0) == 0 || command.rfind("COUNT", 0) == 0) {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

}
