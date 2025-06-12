#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace prokopenko {

  using std::vector;

  void areaCommand(const vector<Polygon>& v, std::istream& in) {
    std::string a;
    in >> a;
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (a == "EVEN" || a == "ODD" || a == "MEAN" ||
      std::all_of(a.begin(), a.end(), ::isdigit)) {
      if (a == "EVEN" || a == "ODD") {
        bool even = (a == "EVEN");
        double s = std::accumulate(v.begin(), v.end(), 0.0,
          [even](double acc, auto& p) {
            return (p.points.size() % 2 == even) ?
              acc + getArea(p) : acc;
          });
        std::cout << s << "\n";
      }
      else if (a == "MEAN") {
        if (v.empty()) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else {
          double t = std::accumulate(v.begin(), v.end(), 0.0,
            [](double acc, auto& p) {
              return acc + getArea(p);
            });
          std::cout << t / v.size() << "\n";
        }
      }
      else {
        size_t n = std::stoul(a);
        if (n < 3) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else {
          double s = std::accumulate(v.begin(), v.end(),
            0.0, [n](double acc, auto& p) {
              return (p.points.size() == n) ?
                acc + getArea(p) : acc;
            });
          std::cout << s << "\n";
        }
      }
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  void countCommand(const vector<Polygon>& v, std::istream& in) {
    std::string a;
    in >> a;
    if (a == "EVEN" || a == "ODD" ||
      std::all_of(a.begin(), a.end(), ::isdigit)) {
      if (a == "EVEN" || a == "ODD") {
        bool even = (a == "EVEN");
        auto c = std::count_if(v.begin(), v.end(),
          [even](auto& p) {
            return p.points.size() % 2 == even;
          });
        std::cout << c << "\n";
      }
      else {
        size_t n = std::stoul(a);
        if (n < 3) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else {
          auto c = std::count_if(v.begin(), v.end(),
            [n](auto& p) {
              return p.points.size() == n;
            });
          std::cout << c << "\n";
        }
      }
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  void maxCommand(const vector<Polygon>& v, std::istream& in) {
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
        [](auto& a, auto& b) {
          return getArea(a) < getArea(b);
        });
      std::cout << getArea(*it) << "\n";
    }
    else {
      auto it = std::max_element(v.begin(), v.end(),
        [](auto& a, auto& b) {
          return a.points.size() < b.points.size();
        });
      std::cout << it->points.size() << "\n";
    }
  }

  void minCommand(const vector<Polygon>& v, std::istream& in) {
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
        [](auto& a, auto& b) {
          return getArea(a) < getArea(b);
        });
      std::cout << getArea(*it) << "\n";
    }
    else {
      auto it = std::min_element(v.begin(), v.end(),
        [](auto& a, auto& b) {
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
    for (size_t i = 0; i < v.size(); i++) {
      if (v[i] == target) {
        v.insert(v.begin() + i + 1, target);
        i++;
        cnt++;
      }
    }
    std::cout << cnt << "\n";
  }

  void rightShapesCommand(const vector<Polygon>& v, std::istream&) {
    size_t cnt = std::count_if(v.begin(), v.end(),
      [](auto& p) {
        return hasRightAngle(p);
      });
    std::cout << cnt << "\n";
  }

}  // namespace prokopenko
