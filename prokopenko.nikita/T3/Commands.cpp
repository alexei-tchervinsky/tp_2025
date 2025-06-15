#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <limits>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // Проверка «уже встречалось» по перестановке
  static bool isDuplicate(const std::vector<Polygon>& seen,
    const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  // AREA <...>
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
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1)
          << (sum / cnt) << '\n';
      }
    }
    else if (!param.empty() &&
      std::all_of(param.begin(), param.end(), ::isdigit)) {
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

  // MAX <AREA|VERTEXES>
  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
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

  // MIN <AREA|VERTEXES>
  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
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

  // MEAN (без аргумента) — аналог AREA MEAN
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

  // COUNT ODD
  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
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
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : unique) {
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
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = 0;
    for (const auto& p : unique) {
      if (p.points.size() == n) ++cnt;
    }
    out << cnt << '\n';
  }

  // SAME <Polygon>
  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double a0 = pattern.getArea();
    if (a0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // RIGHT
  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

  // PERMS <Polygon>
  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    double a0 = pattern.getArea();
    if (a0 > EPS) {
      for (const auto& p : polys) {
        if (p.isPermOf(pattern)) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // LESS <Polygon>
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
      if (a > EPS && a < a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // MORE <Polygon>
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
      if (a > EPS && a > a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // EQUAL <Polygon>
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
        if (std::fabs(p.getArea() - a0) < EPS) ++cnt;
      }
    }
    out << cnt << '\n';
  }

  // MAXSEQ <Polygon>
  void MaxSeq(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t best = 0, cur = 0;
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        ++cur;
        if (cur > best) best = cur;
      }
      else {
        cur = 0;
      }
    }
    out << best << '\n';
  }

  // RMECHO <Polygon>
  void RmEcho(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t removed = 0;
    bool in_seq = false;
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        if (!in_seq) {
          in_seq = true;
        }
        else {
          ++removed;
        }
      }
      else {
        in_seq = false;
      }
    }
    out << removed << '\n';
  }

  // ECHO <Polygon>
  void EchoCmd(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t added = 0;
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        ++added;
      }
    }
    out << added << '\n';
  }

  // LESSAREA <Polygon>
  void LessArea(const std::vector<Polygon>& polys, std::ostream& out) {
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
      if (a > EPS && a < a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // INFRAME <Polygon>
  void InFrame(const std::vector<Polygon>& polys, std::ostream& out) {
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
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();
    for (const auto& poly : polys) {
      for (auto& pt : poly.points) {
        if (pt.x < minX) minX = pt.x;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.y > maxY) maxY = pt.y;
      }
    }
    bool inside = true;
    for (auto& pt : pattern.points) {
      if (pt.x < minX || pt.x > maxX ||
        pt.y < minY || pt.y > maxY) {
        inside = false;
        break;
      }
    }
    out << (inside ? "<TRUE>\n" : "<FALSE>\n");
  }

  // Проверка пересечения отрезков
  static bool segmentsIntersect(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4) {
    auto orient = [](int ax, int ay, int bx, int by,
      int cx, int cy) {
        long long v = static_cast<long long>(bx - ax) * (cy - ay)
          - static_cast<long long>(by - ay) * (cx - ax);
        if (v > 0) return 1;
        if (v < 0) return -1;
        return 0;
      };
    auto onSeg = [](int ax, int ay, int bx, int by,
      int cx, int cy) {
        return std::min(ax, bx) <= cx && cx <= std::max(ax, bx)
          && std::min(ay, by) <= cy && cy <= std::max(ay, by);
      };
    int o1 = orient(x1, y1, x2, y2, x3, y3);
    int o2 = orient(x1, y1, x2, y2, x4, y4);
    int o3 = orient(x3, y3, x4, y4, x1, y1);
    int o4 = orient(x3, y3, x4, y4, x2, y2);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSeg(x1, y1, x2, y2, x3, y3)) return true;
    if (o2 == 0 && onSeg(x1, y1, x2, y2, x4, y4)) return true;
    if (o3 == 0 && onSeg(x3, y3, x4, y4, x1, y1)) return true;
    if (o4 == 0 && onSeg(x3, y3, x4, y4, x2, y2)) return true;
    return false;
  }

  // Точка в полигона (ray casting)
  static bool pointInPoly(const Polygon& poly, const Point& pt) {
    bool inside = false;
    size_t n = poly.points.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
      const auto& pi = poly.points[i];
      const auto& pj = poly.points[j];
      if (((pi.y > pt.y) != (pj.y > pt.y)) &&
        (pt.x < static_cast<long double>(pj.x - pi.x) *
          (pt.y - pi.y) / (pj.y - pi.y) + pi.x)) {
        inside = !inside;
      }
    }
    return inside;
  }

  // INTERSECTIONS <Polygon>
  void Intersections(const std::vector<Polygon>& polys,
    std::ostream& out) {
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
      if (a <= EPS) continue;
      bool inter = false;
      size_t n1 = p.points.size();
      size_t n2 = pattern.points.size();
      for (size_t i = 0; i < n1 && !inter; ++i) {
        int x1 = p.points[i].x;
        int y1 = p.points[i].y;
        int x2 = p.points[(i + 1) % n1].x;
        int y2 = p.points[(i + 1) % n1].y;
        for (size_t j = 0; j < n2; ++j) {
          int x3 = pattern.points[j].x;
          int y3 = pattern.points[j].y;
          int x4 = pattern.points[(j + 1) % n2].x;
          int y4 = pattern.points[(j + 1) % n2].y;
          if (segmentsIntersect(x1, y1, x2, y2, x3, y3, x4, y4)) {
            inter = true;
            break;
          }
        }
      }
      if (!inter) {
        if (pointInPoly(p, pattern.points[0]) ||
          pointInPoly(pattern, p.points[0])) {
          inter = true;
        }
      }
      if (inter) ++cnt;
    }
    out << cnt << '\n';
  }

  // RECTS
  void Rects(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.points.size() != 4) continue;
      bool ok = true;
      for (size_t i = 0; i < 4; ++i) {
        const auto& a = p.points[i];
        const auto& b = p.points[(i + 1) % 4];
        const auto& c = p.points[(i + 2) % 4];
        int dx1 = b.x - a.x;
        int dy1 = b.y - a.y;
        int dx2 = c.x - b.x;
        int dy2 = c.y - b.y;
        if (dx1 * dx2 + dy1 * dy2 != 0) {
          ok = false;
          break;
        }
      }
      if (ok) ++cnt;
    }
    out << cnt << '\n';
  }

  // RIGHTSHAPES
  void RightShapes(const std::vector<Polygon>& polys,
    std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
