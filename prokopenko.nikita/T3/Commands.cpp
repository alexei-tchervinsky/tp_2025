#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <limits>
#include <climits>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  static bool isDuplicate(const std::vector<Polygon>& seen, const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (param == "EVEN" || param == "ODD") {
      double sum = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS &&
          ((param == "EVEN") == (p.points.size() % 2 == 0))) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (param == "MEAN") {
      double sum = 0.0;
      size_t count = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          sum += a;
          ++count;
        }
      }
      if (count == 0) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << sum / count << '\n';
      }
    }
    else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
      size_t n = std::stoul(param);
      if (n < 3) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      for (const auto& p : polys) {
        if (p.points.size() == n) {
          double a = p.getArea();
          if (a > EPS) sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t count = 0;
    for (const auto& p : unique) {
      if (p.points.size() % 2 == 1) ++count;
    }
    out << count << '\n';
  }

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t count = 0;
    for (const auto& p : unique) {
      if (p.points.size() % 2 == 0) ++count;
    }
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t count = 0;
    for (const auto& p : unique) {
      if (p.points.size() == n) ++count;
    }
    out << count << '\n';
  }

  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (param == "AREA") {
      double maxA = -1.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > maxA) maxA = a;
      }
      if (maxA < EPS) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << maxA << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t maxV = 0;
      for (const auto& p : polys) {
        if (p.getArea() > EPS && p.points.size() > maxV) {
          maxV = p.points.size();
        }
      }
      if (maxV == 0) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << maxV << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    double sum = 0.0;
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS) {
        sum += a;
        ++count;
      }
    }
    if (count == 0) {
      out << "<INVALID COMMAND>\n";
    }
    else {
      out << std::fixed << std::setprecision(1) << sum / count << '\n';
    }
  }

  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) ++count;
    }
    out << count << '\n';
  }

  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t count = 0;
    for (const auto& p : polys) {
      if (p.isRight() && p.getArea() > EPS) ++count;
    }
    out << count << '\n';
  }

  void Rects(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t count = 0;
    for (const auto& p : polys) {
      if (p.points.size() == 4 && p.isRight()) ++count;
    }
    out << count << '\n';
  }

  void RightShapes(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t count = 0;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && p.isRight()) ++count;
    }
    out << count << '\n';
  }

} // namespace prokopenko
