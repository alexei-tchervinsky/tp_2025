#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // Проверка равенства площадей с допуском EPS
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }
  // Проверка-дубликат: есть ли полигон q в списке seen, такой что p.isPermOf(q)
  static bool isDuplicate(const std::vector<Polygon>& seen, const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  // AREA <param>
  void Area(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    std::string param;
    if (!(in >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN") {
      double s = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 0)) {
          s += a;
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "ODD") {
      double s = 0.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 1)) {
          s += a;
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "MEAN") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double s = 0.0;
      size_t cnt = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          s += a;
          ++cnt;
        }
      }
      if (cnt == 0) {
        out << "0.0\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << (s / cnt) << '\n';
      }
    }
    else if (!param.empty() && std::all_of(param.begin(), param.end(), ::isdigit)) {
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
        double a = p.getArea();
        if (a > EPS && p.points.size() == n) {
          s += a;
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MAX <param>
  void Max(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    std::string param;
    if (!(in >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = -1.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || a > mval) {
            mval = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << mval << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || p.points.size() > mv) {
            mv = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MIN <param>
  void Min(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    std::string param;
    if (!(in >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = 0.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || a < mval) {
            mval = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << mval << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!found || p.points.size() < mv) {
            mv = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MEAN без параметра
  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double s = 0.0;
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS) {
        s += a;
        ++cnt;
      }
    }
    if (cnt == 0) {
      out << "<INVALID COMMAND>\n";
    }
    else {
      out << std::fixed << std::setprecision(1) << (s / cnt) << '\n';
    }
  }

  // SAME <n> <polygon>
  void Same(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    size_t n;
    if (!(in >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(in >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    // проверяем площадь паттерна
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // RIGHT без параметра
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

  // PERMS <n> <polygon>
  void Perms(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    size_t n;
    if (!(in >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(in >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // LESS <polygon>
  void Less(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    Polygon pattern;
    if (!(in >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // MORE <polygon>
  void More(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    Polygon pattern;
    if (!(in >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a > a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // EQUAL <polygon>
  void Equal(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    Polygon pattern;
    if (!(in >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (equalArea(p, pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // COUNT <ODD|EVEN|n>
  void Count(const std::vector<Polygon>& polys, std::istream& in, std::ostream& out) {
    std::string param;
    if (!(in >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "ODD") {
      CountOdd(polys, out);
    }
    else if (param == "EVEN") {
      CountEven(polys, out);
    }
    else if (!param.empty() && std::all_of(param.begin(), param.end(), ::isdigit)) {
      try {
        size_t n = std::stoul(param);
        CountN(polys, out, n);
      }
      catch (...) {
        out << "<INVALID COMMAND>\n";
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // COUNT ODD: только неповторяющиеся (по пермутации) полигональные формы с a>EPS
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : unique) {
      if (p.points.size() % 2 == 1) ++cnt;
    }
    out << cnt << '\n';
  }

  // COUNT EVEN
  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : unique) {
      if (p.points.size() % 2 == 0) ++cnt;
    }
    out << cnt << '\n';
  }

  // COUNT n
  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : unique) {
      if (p.points.size() == n) ++cnt;
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
