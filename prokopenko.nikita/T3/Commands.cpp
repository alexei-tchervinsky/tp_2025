#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // проверка равенства площадей с EPS
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // вспомогательная: фильтрация уникальных по перестановке
  static bool isDuplicate(const std::vector<Polygon>& seen, const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  // AREA <param>
  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    // EVEN / ODD
    if (param == "EVEN" || param == "ODD") {
      bool wantEven = (param == "EVEN");
      double sum = 0.0;
      // учитываем только уникальные с площадью>0 и корректные (в main уже отфильтрованы)
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          if ((p.points.size() % 2 == 0) == wantEven) {
            sum += a;
          }
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (param == "MEAN") {
      // MEAN: если нет уникальных с area>0 → INVALID
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
        }
      }
      if (uniq.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      for (const auto& p : uniq) {
        sum += p.getArea();
      }
      double mean = sum / uniq.size();
      out << std::fixed << std::setprecision(1) << mean << '\n';
    }
    else if (!param.empty() && std::all_of(param.begin(), param.end(), ::isdigit)) {
      // AREA <n>
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
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && p.points.size() == n && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
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
      double best = -1.0;
      bool found = false;
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          if (!found || a > best) {
            best = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << best << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t best = 0;
      bool found = false;
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          if (!found || p.points.size() > best) {
            best = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << best << '\n';
      }
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
      double best = 0.0;
      bool found = false;
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          if (!found || a < best) {
            best = a;
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << best << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t best = 0;
      bool found = false;
      std::vector<Polygon> uniq;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && !isDuplicate(uniq, p)) {
          uniq.push_back(p);
          if (!found || p.points.size() < best) {
            best = p.points.size();
            found = true;
          }
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << best << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MEAN (как отдельная команда, без параметра после слова MEAN в main)
  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    // эквивалент AREA MEAN
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
      }
    }
    if (uniq.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double sum = 0.0;
    for (const auto& p : uniq) sum += p.getArea();
    out << std::fixed << std::setprecision(1) << (sum / uniq.size()) << '\n';
  }

  // COUNT ODD
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : uniq) {
      if (p.points.size() % 2 == 1) ++cnt;
    }
    out << cnt << '\n';
  }

  // COUNT EVEN
  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : uniq) {
      if (p.points.size() % 2 == 0) ++cnt;
    }
    out << cnt << '\n';
  }

  // COUNT <n>
  void CountN(const std::vector<Polygon>& polys,
    std::ostream& out,
    size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : uniq) {
      if (p.points.size() == n) ++cnt;
    }
    out << cnt << '\n';
  }

  // SAME <n> <polygon>
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
    if (pattern.points.size() != n) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    std::vector<Polygon> uniq; // уникальные из polys
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        // сравнить с pattern: равенство по перестановке
        if (p.isPermOf(pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // RIGHT
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        if (p.isRight()) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // PERMS <n> <polygon>
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
    if (pattern.points.size() != n) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        if (p.isPermOf(pattern)) ++cnt;
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
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        if (a < a0) ++cnt;
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
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        if (a > a0) ++cnt;
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
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && !isDuplicate(uniq, p)) {
        uniq.push_back(p);
        if (equalArea(p, pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
