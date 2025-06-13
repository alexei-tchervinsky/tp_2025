#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  constexpr double EPS = 1e-6;

  // Сумма площадей всех полигонов
  static double sumAreas(const std::vector<Polygon>& polys) {
    return std::accumulate(polys.begin(), polys.end(), 0.0,
      [](double acc, const Polygon& p) {
        return acc + p.getArea();
      });
  }

  // Равенство площадей с погрешностью EPS
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // ===== AREA =====
  // Обработка команды "AREA <subcmd>"
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
        out << "<EMPTY DATASET>\n";
        return;
      }
      double s = sumAreas(polys);
      double mean = s / polys.size();
      out << std::fixed << std::setprecision(1) << mean << '\n';
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

  // ===== MAX =====
  // Обработка "MAX <subcmd>"
  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      if (polys.empty()) {
        out << "<EMPTY DATASET>\n";
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
        out << "<EMPTY DATASET>\n";
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

  // ===== MIN =====
  // Обработка "MIN <subcmd>"
  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      if (polys.empty()) {
        out << "<EMPTY DATASET>\n";
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
        out << "<EMPTY DATASET>\n";
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

  // ===== COUNT =====
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 1) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }
  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }
  void CountN(const std::vector<Polygon>& polys,
    std::ostream& out,
    size_t n)
  {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() == n) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== SAME =====
  // Ожидает после "SAME" параметр: число и точки в формате чтения Polygon
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
      if (p.isPermOf(pattern)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== RIGHT =====
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.isRight()) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== PERMS =====
  // Ожидает после "PERMS" параметр: число и точки для pattern
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
      if (p.isPermOf(pattern)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== LESS =====
  // Ожидает polygon после "LESS"
  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() < a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== MORE =====
  // Ожидает polygon после "MORE"
  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() > a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // ===== EQUAL =====
  // Ожидает polygon после "EQUAL"
  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (equalArea(p, pattern)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
