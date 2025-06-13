#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <functional>
#include <set>

namespace prokopenko
{
  constexpr double EPS = 1e-6;

  // Вспомогательная сумма площадей
  static double sumAreas(const std::vector<Polygon>& polys) {
    return std::accumulate(polys.begin(), polys.end(), 0.0,
      [](double acc, const Polygon& p) {
        return acc + p.getArea();
      });
  }

  // Проверка равенства площадей с EPS
  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // ===== AREA =====
  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    double total = sumAreas(polys);
    out << std::fixed << std::setprecision(1) << total << '\n';
  }

  void AreaEven(const std::vector<Polygon>& polys, std::ostream& out) {
    double s = 0.0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 0) {
        s += p.getArea();
      }
    }
    out << std::fixed << std::setprecision(1) << s << '\n';
  }

  void AreaOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    double s = 0.0;
    for (const auto& p : polys) {
      if (p.points.size() % 2 == 1) {
        s += p.getArea();
      }
    }
    out << std::fixed << std::setprecision(1) << s << '\n';
  }

  void AreaMean(const std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<EMPTY DATASET>\n";
      return;
    }
    double s = sumAreas(polys);
    double mean = s / polys.size();
    out << std::fixed << std::setprecision(1) << mean << '\n';
  }

  void AreaN(const std::vector<Polygon>& polys,
    std::ostream& out,
    size_t n)
  {
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

  // ===== MAX =====
  void MaxArea(const std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<EMPTY DATASET>\n";
      return;
    }
    const Polygon* mx = &polys.front();
    double mval = polys.front().getArea();
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > mval) {
        mval = a;
        mx = &p;
      }
    }
    out << std::fixed << std::setprecision(1) << mval << '\n';
  }

  void MaxVertexes(const std::vector<Polygon>& polys, std::ostream& out) {
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

  // ===== MIN =====
  void MinArea(const std::vector<Polygon>& polys, std::ostream& out) {
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

  void MinVertexes(const std::vector<Polygon>& polys, std::ostream& out) {
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
  // ЗДЕСЬ: реализация в main: main читает параметр(ы) после "SAME" и вызывает
  // соответствующую функцию, например SamePattern(data, pattern, out).
  void Same(const std::vector<Polygon>&, std::ostream& out) {
    out << "<INVALID COMMAND>\n";
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
  void Perms(const std::vector<Polygon>&, std::ostream& out) {
    out << "<INVALID COMMAND>\n";
  }

  // ===== LESS / MORE / EQUAL =====
  void Less(const std::vector<Polygon>&, std::ostream& out) {
    out << "<INVALID COMMAND>\n";
  }
  void More(const std::vector<Polygon>&, std::ostream& out) {
    out << "<INVALID COMMAND>\n";
  }
  void Equal(const std::vector<Polygon>&, std::ostream& out) {
    out << "<INVALID COMMAND>\n";
  }

} // namespace prokopenko
