#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <limits>
#include <tuple>
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
        bool isEven = (p.points.size() % 2 == 0);
        if (a > EPS && ((param == "EVEN") == isEven)) {
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

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t count = 0;
    std::vector<Polygon> seen;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(seen, p)) {
        if (p.points.size() % 2 == 0) ++count;
        seen.push_back(p);
      }
    }
    out << count << '\n';
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t count = 0;
    std::vector<Polygon> seen;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(seen, p)) {
        if (p.points.size() % 2 == 1) ++count;
        seen.push_back(p);
      }
    }
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    std::vector<Polygon> seen;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && !isDuplicate(seen, p)) {
        if (p.points.size() == n) ++count;
        seen.push_back(p);
      }
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

  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (param == "AREA") {
      double minA = -1.0;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (minA < 0 || a < minA)) minA = a;
      }
      if (minA < 0) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << minA << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t minV = 0;
      for (const auto& p : polys) {
        if (p.getArea() > EPS && (minV == 0 || p.points.size() < minV)) {
          minV = p.points.size();
        }
      }
      if (minV == 0) {
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
      if (p.getArea() > EPS && p.isRight()) ++count;
    }
    out << count << '\n';
  }

  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref) || ref.getArea() <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) ++count;
    }
    out << count << '\n';
  }

  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double areaRef = ref.getArea();
    if (areaRef <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < areaRef) ++count;
    }
    out << count << '\n';
  }

  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double areaRef = ref.getArea();
    if (areaRef <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a > areaRef) ++count;
    }
    out << count << '\n';
  }

  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double areaRef = ref.getArea();
    if (areaRef <= EPS) {
      out << "0\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      if (std::fabs(p.getArea() - areaRef) < EPS) ++count;
    }
    out << count << '\n';
  }

  void MaxSeq(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t maxLen = 0, curLen = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) {
        ++curLen;
        if (curLen > maxLen) maxLen = curLen;
      }
      else {
        curLen = 0;
      }
    }
    out << maxLen << '\n';
  }

  void RmEcho(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t removed = 0;
    bool inSeq = false;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) {
        if (inSeq) ++removed;
        inSeq = true;
      }
      else {
        inSeq = false;
      }
    }
    out << removed << '\n';
  }

  void EchoCmd(const std::vector<Polygon>& polys, std::ostream& out) {
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

  void LessArea(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double areaRef = ref.getArea();
    if (areaRef <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < areaRef) ++count;
    }
    out << count << '\n';
  }

  void InFrame(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon shape;
    if (!(std::cin >> shape) || shape.getArea() <= EPS || polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;
    for (const auto& p : polys) {
      for (const auto& pt : p.points) {
        minX = std::min(minX, pt.x);
        maxX = std::max(maxX, pt.x);
        minY = std::min(minY, pt.y);
        maxY = std::max(maxY, pt.y);
      }
    }
    for (const auto& pt : shape.points) {
      if (pt.x < minX || pt.x > maxX || pt.y < minY || pt.y > maxY) {
        out << "<FALSE>\n";
        return;
      }
    }
    out << "<TRUE>\n";
  }

  static bool segmentsIntersect(int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4) {
    auto orientation = [](int ax, int ay, int bx, int by, int cx, int cy) {
      long long v = static_cast<long long>(bx - ax) * (cy - ay)
        - static_cast<long long>(by - ay) * (cx - ax);
      return (v > 0) - (v < 0);
      };
    auto onSegment = [](int ax, int ay, int bx, int by, int cx, int cy) {
      return std::min(ax, bx) <= cx && cx <= std::max(ax, bx)
        && std::min(ay, by) <= cy && cy <= std::max(ay, by);
      };
    int o1 = orientation(x1, y1, x2, y2, x3, y3);
    int o2 = orientation(x1, y1, x2, y2, x4, y4);
    int o3 = orientation(x3, y3, x4, y4, x1, y1);
    int o4 = orientation(x3, y3, x4, y4, x2, y2);

    return (o1 != o2 && o3 != o4) ||
      (o1 == 0 && onSegment(x1, y1, x2, y2, x3, y3)) ||
      (o2 == 0 && onSegment(x1, y1, x2, y2, x4, y4)) ||
      (o3 == 0 && onSegment(x3, y3, x4, y4, x1, y1)) ||
      (o4 == 0 && onSegment(x3, y3, x4, y4, x2, y2));
  }

  static bool pointInPolygon(const Polygon& poly, const Point& pt) {
    bool inside = false;
    size_t n = poly.points.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
      const Point& a = poly.points[i];
      const Point& b = poly.points[j];
      if ((a.y > pt.y) != (b.y > pt.y) &&
        pt.x < (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 0.0) + a.x) {
        inside = !inside;
      }
    }
    return inside;
  }

  void Intersections(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon shape;
    if (!(std::cin >> shape) || shape.getArea() <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    size_t count = 0;
    for (const auto& poly : polys) {
      if (poly.getArea() <= EPS) continue;
      bool intersects = false;
      size_t n1 = poly.points.size(), n2 = shape.points.size();
      for (size_t i = 0; i < n1 && !intersects; ++i) {
        int x1 = poly.points[i].x, y1 = poly.points[i].y;
        int x2 = poly.points[(i + 1) % n1].x, y2 = poly.points[(i + 1) % n1].y;
        for (size_t j = 0; j < n2; ++j) {
          int x3 = shape.points[j].x, y3 = shape.points[j].y;
          int x4 = shape.points[(j + 1) % n2].x, y4 = shape.points[(j + 1) % n2].y;
          if (segmentsIntersect(x1, y1, x2, y2, x3, y3, x4, y4)) {
            intersects = true;
            break;
          }
        }
      }
      if (!intersects) {
        intersects = pointInPolygon(poly, shape.points[0]) ||
          pointInPolygon(shape, poly.points[0]);
      }
      if (intersects) ++count;
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
