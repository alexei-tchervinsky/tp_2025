#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // сравнение площадей с допуском
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN") {
      double sum = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 0)) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (param == "ODD") {
      double sum = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 1)) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (param == "MEAN") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      size_t cnt = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          sum += a;
          ++cnt;
        }
      }
      if (cnt == 0) {
        out << "0.0\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << (sum / cnt) << '\n';
      }
    }
    else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
      size_t n;
      try {
        n = std::stoul(param);
      }
      catch (...) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      if (n < 3) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && p.points.size() == n) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double maxA = -1.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || a > maxA) {
            maxA = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << maxA << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t maxV = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || p.points.size() > maxV) {
            maxV = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
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

  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double minA = 0.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || a < minA) {
            minA = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << minA << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t minV = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || p.points.size() < minV) {
            minV = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << minV << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double sum = 0.0;
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS) {
        sum += a;
        ++cnt;
      }
    }
    if (cnt == 0) {
      out << "<INVALID COMMAND>\n";
    }
    else {
      out << std::fixed << std::setprecision(1) << (sum / cnt) << '\n';
    }
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && (p.points.size() % 2 == 1)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && (p.points.size() % 2 == 0)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void CountN(const std::vector<Polygon>& polys,
    std::ostream& out,
    size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && p.points.size() == n) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double A0 = pattern.getArea();
    if (A0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double A0 = pattern.getArea();
    if (A0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double A0 = pattern.getArea();
    if (A0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < A0) ++cnt;
    }
    out << cnt << '\n';
  }

  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double A0 = pattern.getArea();
    if (A0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a > A0) ++cnt;
    }
    out << cnt << '\n';
  }

  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double A0 = pattern.getArea();
    if (A0 > EPS) {
      for (const auto& p : polys) {
        if (equalArea(p, pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
