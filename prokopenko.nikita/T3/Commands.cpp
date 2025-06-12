#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace prokopenko {

  void areaCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string a;
    in >> a;
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (a == "EVEN" || a == "ODD") {
      bool even = (a == "EVEN");
      double s = std::accumulate(v.begin(), v.end(), 0.0,
        [even](double acc, const Polygon& p) {
          return (p.points.size() % 2 == even)
            ? acc + getArea(p) : acc;
        });
      std::cout << s << "\n";
    }
    else if (a == "MEAN") {
      if (v.empty()) {
        std::cout << "<INVALID COMMAND>\n";
      }
      else {
        double t = std::accumulate(v.begin(), v.end(), 0.0,
          [](double acc, const Polygon& p) {
            return acc + getArea(p);
          });
        std::cout << t / v.size() << "\n";
      }
    }
    else {
      size_t n;
      std::istringstream iss(a);
      if (!(iss >> n) || n < 3) {
        std::cout << "<INVALID COMMAND>\n";
      }
      else {
        double s = std::accumulate(v.begin(), v.end(), 0.0,
          [n](double acc, const Polygon& p) {
            return (p.points.size() == n)
              ? acc + getArea(p) : acc;
          });
        std::cout << s << "\n";
      }
    }
  }

  void countCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string a;
    in >> a;
    if (a == "EVEN" || a == "ODD") {
      bool even = (a == "EVEN");
      auto c = std::count_if(v.begin(), v.end(),
        [even](const Polygon& p) {
          return p.points.size() % 2 == even;
        });
      std::cout << c << "\n";
    }
    else {
      size_t n;
      std::istringstream iss(a);
      if (!(iss >> n) || n < 3) {
        std::cout << "<INVALID COMMAND>\n";
      }
      else {
        auto c = std::count_if(v.begin(), v.end(),
          [n](const Polygon& p) {
            return p.points.size() == n;
          });
        std::cout << c << "\n";
      }
    }
  }

  void maxCommand(const std::vector<Polygon>& v, std::istream& in) {
    std::string a;
    in >> a;
    if (v.empty() || (a != "AREA" && a != "VERTEXES")) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (a == "AREA") {
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
    std::string a;
    in >> a;
    if (v.empty() || (a != "AREA" && a != "VERTEXES")) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (a == "AREA") {
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
    size_t cnt = 0;
    for (size_t i = 0; i < v.size(); ++i) {
      if (v[i] == target) {
        v.insert(v.begin() + i + 1, target);
        i++;
        cnt++;
      }
    }
    std::cout << cnt << "\n";
  }

  void rightShapesCommand(const std::vector<Polygon>& v, std::istream&) {
    auto cnt = std::count_if(v.begin(), v.end(),
      [](const Polygon& p) {
        return hasRightAngle(p);
      });
    std::cout << cnt << "\n";
  }

}
