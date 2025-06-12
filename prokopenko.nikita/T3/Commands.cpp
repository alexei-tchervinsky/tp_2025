#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <sstream>

namespace prokopenko {

  void areaCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string arg;
    in >> arg;
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (arg == "EVEN" || arg == "ODD") {
      bool even = (arg == "EVEN");
      double s = std::accumulate(v.begin(), v.end(), 0.0,
        [even](double acc, const Polygon& p) {
          return (p.points.size() % 2 == even) ? acc + getArea(p) : acc;
        });
      std::cout << s << "\n";
    }
    else if (arg == "MEAN") {
      if (v.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      double total = std::accumulate(v.begin(), v.end(), 0.0,
        [](double acc, const Polygon& p) {
          return acc + getArea(p);
        });
      std::cout << total / v.size() << "\n";
    }
    else {
      size_t n;
      std::istringstream iss(arg);
      if (!(iss >> n) || n < 3) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      double s = std::accumulate(v.begin(), v.end(), 0.0,
        [n](double acc, const Polygon& p) {
          return (p.points.size() == n) ? acc + getArea(p) : acc;
        });
      std::cout << s << "\n";
    }
  }

  void countCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string arg;
    in >> arg;
    if (arg == "EVEN" || arg == "ODD") {
      bool even = (arg == "EVEN");
      auto c = std::count_if(v.begin(), v.end(),
        [even](const Polygon& p) {
          return p.points.size() % 2 == even;
        });
      std::cout << c << "\n";
    }
    else {
      size_t n;
      std::istringstream iss(arg);
      if (!(iss >> n) || n < 3) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      auto c = std::count_if(v.begin(), v.end(),
        [n](const Polygon& p) {
          return p.points.size() == n;
        });
      std::cout << c << "\n";
    }
  }

  void maxCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string arg;
    in >> arg;
    if (v.empty() || (arg != "AREA" && arg != "VERTEXES")) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (arg == "AREA") {
      iofmtguard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1);
      auto it = std::max_element(v.begin(), v.end(),
        [](const Polygon& a, const Polygon& b) {
          return getArea(a) < getArea(b);
        });
      std::cout << getArea(*it) << "\n";
    }
    else {
      auto it = std::max_element(v.begin(), v.end(),
        [](const Polygon& a, const Polygon& b) {
          return a.points.size() < b.points.size();
        });
      std::cout << it->points.size() << "\n";
    }
  }

  void minCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string arg;
    in >> arg;
    if (v.empty() || (arg != "AREA" && arg != "VERTEXES")) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (arg == "AREA") {
      iofmtguard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1);
      auto it = std::min_element(v.begin(), v.end(),
        [](const Polygon& a, const Polygon& b) {
          return getArea(a) < getArea(b);
        });
      std::cout << getArea(*it) << "\n";
    }
    else {
      auto it = std::min_element(v.begin(), v.end(),
        [](const Polygon& a, const Polygon& b) {
          return a.points.size() < b.points.size();
        });
      std::cout << it->points.size() << "\n";
    }
  }

  void echoCommand(std::vector<Polygon>& v, std::istream& in) {
    Polygon target;
    if (!(in >> target)) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (size_t i = 0; i < v.size(); ++i) {
      if (v[i] == target) {
        v.insert(v.begin() + i + 1, target);
        ++i;
        ++count;
      }
    }
    std::cout << count << "\n";
  }

  void rightShapesCommand(const std::vector<Polygon>& v, std::istream&) {
    auto c = std::count_if(v.begin(), v.end(),
      [](const Polygon& p) {
        return hasRightAngle(p);
      });
    std::cout << c << "\n";
  }

  void doCommand(const std::string& cmd, std::vector<Polygon>& v, std::istream& in) {
    if (cmd == "AREA") areaCommand(v, in);
    else if (cmd == "COUNT") countCommand(v, in);
    else if (cmd == "MAX") maxCommand(v, in);
    else if (cmd == "MIN") minCommand(v, in);
    else if (cmd == "ECHO") echoCommand(v, in);
    else if (cmd == "RIGHTSHAPES") rightShapesCommand(v, in);
    else std::cout << "<INVALID COMMAND>\n";
  }

}
