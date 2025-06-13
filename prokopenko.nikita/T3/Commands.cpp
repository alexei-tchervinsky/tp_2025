#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // Сумма площадей
  static double sumAreas(const std::vector<Polygon>& polys) {
    return std::accumulate(polys.begin(), polys.end(), 0.0,
      [](double acc, const Polygon& p) {
        return acc + p.getArea();
      });
  }
  // Проверка равенства площадей
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // AREA <param>
  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN") {
      double s = 0.0;
      for (const auto& p : polys) {
        if (p.points.size() % 2 == 0) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "ODD") {
      double s = 0.0;
      for (const auto& p : polys) {
        if (p.points.size() % 2 == 1) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "MEAN") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double s = sumAreas(polys);
      out << std::fixed << std::setprecision(1) << (s / polys.size()) << '\n';
    }
    else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
      size_t n = 0;
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
      double s = 0.0;
      for (const auto& p : polys) {
        if (p.points.size() == n) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MAX <param>
  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double mval = polys.front().getArea();
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > mval) {
          mval = a;
        }
      }
      out << std::fixed << std::setprecision(1) << mval << '\n';
    }
    else if (param == "VERTEXES") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      size_t mv = polys.front().points.size();
      for (const auto& p : polys) {
        mv = std::max(mv, p.points.size());
      }
      out << mv << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MIN <param>
  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double mval = polys.front().getArea();
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a < mval) {
          mval = a;
        }
      }
      out << std::fixed << std::setprecision(1) << mval << '\n';
    }
    else if (param == "VERTEXES") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      size_t mv = polys.front().points.size();
      for (const auto& p : polys) {
        mv = std::min(mv, p.points.size());
      }
      out << mv << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MEAN
  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double s = sumAreas(polys);
    out << std::fixed << std::setprecision(1) << (s / polys.size()) << '\n';
  }

  // COUNT ODD
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 1) ++cnt;
    }
    out << cnt << '\n';
  }
  // COUNT EVEN
  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 0) ++cnt;
    }
    out << cnt << '\n';
  }
  // COUNT N
  void CountN(const std::vector<Polygon>& polys,
    std::ostream& out,
    size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() == n) ++cnt;
    }
    out << cnt << '\n';
  }

  // SAME N polygon
  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n = 0;
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
    for (const auto& p : polys) {
      if (p.isPermOf(pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // RIGHT
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

  // PERMS N polygon
  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n = 0;
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
    for (const auto& p : polys) {
      if (p.isPermOf(pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // LESS polygon
  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() < a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // MORE polygon
  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() > a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // EQUAL polygon
  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (equalArea(p, pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
