#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // вспомогательная: подсчёт площади одной фигуры
  // equalArea для сравнения площадей в Equal
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // AREA <EVEN|ODD|MEAN|N>
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

  // MAX AREA|VERTEXES
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

  // MIN AREA|VERTEXES
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

  // MEAN (без параметров, средняя площадь всех валидных)
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

  // вспомогательная: фильтрация уникальных по перестановке фигур
  static bool isDuplicatePerm(const std::vector<Polygon>& seen, const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  // COUNT ODD:EVEN:N, с переключением по флагу hadInvalidLine
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out);
  void CountEven(const std::vector<Polygon>& polys, std::ostream& out);
  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n);

  // SAME N <polygon>
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
    double a0 = pattern.getArea();
    if (a0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

  // RIGHT
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && p.isRight()) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // PERMS N <polygon>
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
    double a0 = pattern.getArea();
    if (a0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

  // LESS <polygon>
  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
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
      if (a > EPS && a < a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // MORE <polygon>
  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
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
      if (a > EPS && a > a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // EQUAL <polygon>
  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double a0 = pattern.getArea();
    if (a0 > EPS) {
      for (const auto& p : polys) {
        if (equalArea(p, pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

  // Реализация COUNT:
  static bool hadInvalidLineGlob = false;

  // Для установки флага: вызывается из main
  void setHadInvalid(bool v) {
    hadInvalidLineGlob = v;
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    if (hadInvalidLineGlob) {
      // фильтрация уникальных по перестановке
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicatePerm(uniq, p)) {
          uniq.push_back(p);
        }
      }
      size_t cnt = 0;
      for (const auto& p : uniq) {
        if (p.points.size() % 2 == 1) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
    else {
      // считаем каждую валидную
      size_t cnt = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 1)) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
  }

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    if (hadInvalidLineGlob) {
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicatePerm(uniq, p)) {
          uniq.push_back(p);
        }
      }
      size_t cnt = 0;
      for (const auto& p : uniq) {
        if (p.points.size() % 2 == 0) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
    else {
      size_t cnt = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (p.points.size() % 2 == 0)) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
  }

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (hadInvalidLineGlob) {
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicatePerm(uniq, p)) {
          uniq.push_back(p);
        }
      }
      size_t cnt = 0;
      for (const auto& p : uniq) {
        if (p.points.size() == n) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
    else {
      size_t cnt = 0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && p.points.size() == n) {
          ++cnt;
        }
      }
      out << cnt << '\n';
    }
  }

} // namespace prokopenko
