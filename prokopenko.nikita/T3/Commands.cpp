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

  // AREA <EVEN|ODD|MEAN|num>
  void Area(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN" || param == "ODD") {
      bool wantEven = (param == "EVEN");
      double sum = 0.0;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if ((p.points.size() % 2 == 0) == wantEven) {
            sum += a;
          }
        }
      }
      out << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (param == "MEAN") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      size_t cnt = 0;
      for (auto& p : polys) {
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
        out << std::fixed << std::setprecision(1) << (sum / cnt) << "\n";
      }
    }
    else if (!param.empty()
      && std::all_of(param.begin(), param.end(), ::isdigit)) {
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
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && p.points.size() == n) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MAX <AREA|VERTEXES>
  void Max(std::vector<Polygon>& polys, std::ostream& out) {
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
      double m = -std::numeric_limits<double>::infinity();
      bool any = false;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          any = true;
          if (a > m) m = a;
        }
      }
      if (!any) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << m << "\n";
      }
    }
    else if (param == "VERTEXES") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      size_t mv = 0;
      bool any = false;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          any = true;
          mv = std::max(mv, p.points.size());
        }
      }
      if (!any) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << "\n";
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MIN <AREA|VERTEXES>
  void Min(std::vector<Polygon>& polys, std::ostream& out) {
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
      double m = std::numeric_limits<double>::infinity();
      bool any = false;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          any = true;
          if (a < m) m = a;
        }
      }
      if (!any) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << m << "\n";
      }
    }
    else if (param == "VERTEXES") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      size_t mv = 0;
      bool any = false;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if (!any) {
            mv = p.points.size();
          }
          else {
            mv = std::min(mv, p.points.size());
          }
          any = true;
        }
      }
      if (!any) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << "\n";
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // MEAN (standalone, similar to AREA MEAN)
  void Mean(std::vector<Polygon>& polys, std::ostream& out) {
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double sum = 0.0;
    size_t cnt = 0;
    for (auto& p : polys) {
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
      out << std::fixed << std::setprecision(1) << (sum / cnt) << "\n";
    }
  }

  // COUNT <EVEN|ODD|num>
  void Count(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN" || param == "ODD") {
      bool wantEven = (param == "EVEN");
      size_t cnt = 0;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS) {
          if ((p.points.size() % 2 == 0) == wantEven) {
            ++cnt;
          }
        }
      }
      out << cnt << "\n";
    }
    else if (!param.empty()
      && std::all_of(param.begin(), param.end(), ::isdigit)) {
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
      size_t cnt = 0;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && p.points.size() == n) {
          ++cnt;
        }
      }
      out << cnt << "\n";
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  // PERMS <Polygon>
  void Perms(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (auto& p : polys) {
      if (p.isPermOf(pattern)) {
        ++cnt;
      }
    }
    out << cnt << "\n";
  }

  // MAXSEQ <Polygon>
  void MaxSeq(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t best = 0;
    size_t cur = 0;
    for (auto& p : polys) {
      if (p.isPermOf(pattern)) {
        ++cur;
        best = std::max(best, cur);
      }
      else {
        cur = 0;
      }
    }
    out << best << "\n";
  }

  // RMECHO <Polygon>
  void RmEcho(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t removed = 0;
    // Remove consecutive duplicates equal to pattern
    for (size_t i = 0; i + 1 < polys.size(); ) {
      if (polys[i].isPermOf(pattern)
        && polys[i + 1].isPermOf(pattern)) {
        polys.erase(polys.begin() + (i + 1));
        ++removed;
      }
      else {
        ++i;
      }
    }
    out << removed << "\n";
  }

  // ECHO <Polygon>
  void Echo(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t added = 0;
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        polys.insert(polys.begin() + i + 1, pattern);
        ++added;
        ++i;
      }
    }
    out << added << "\n";
  }

  // LESSAREA <Polygon>
  void LessArea(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (auto& p : polys) {
      double a = p.getArea();
      if (a + EPS < a0) {
        ++cnt;
      }
    }
    out << cnt << "\n";
  }

  // INFRAME <Polygon>
  void InFrame(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (polys.empty()) {
      out << "<FALSE>\n";
      return;
    }
    // compute bounding rect of all stored polygons
    int minx = std::numeric_limits<int>::max();
    int miny = std::numeric_limits<int>::max();
    int maxx = std::numeric_limits<int>::min();
    int maxy = std::numeric_limits<int>::min();
    for (auto& poly : polys) {
      for (auto& pt : poly.points) {
        minx = std::min(minx, pt.x);
        miny = std::min(miny, pt.y);
        maxx = std::max(maxx, pt.x);
        maxy = std::max(maxy, pt.y);
      }
    }
    bool ok = true;
    for (auto& pt : pattern.points) {
      if (pt.x < minx || pt.x > maxx
        || pt.y < miny || pt.y > maxy) {
        ok = false;
        break;
      }
    }
    out << (ok ? "<TRUE>\n" : "<FALSE>\n");
  }

  // INTERSECTIONS <Polygon>
  static bool onSegment(const Point& a, const Point& b,
    const Point& p) {
    if (std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)
      && std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y)) {
      long long cross = static_cast<long long>(b.x - a.x) *
        (p.y - a.y)
        - static_cast<long long>(b.y - a.y) *
        (p.x - a.x);
      return cross == 0;
    }
    return false;
  }
  static int orientation(const Point& a, const Point& b,
    const Point& c) {
    long long v = static_cast<long long>(b.y - a.y) *
      (c.x - b.x)
      - static_cast<long long>(b.x - a.x) *
      (c.y - b.y);
    if (v == 0) return 0;
    return (v > 0 ? 1 : 2);
  }
  static bool segmentsIntersect(const Point& p1,
    const Point& q1,
    const Point& p2,
    const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;
    return false;
  }
  static bool polyIntersect(const Polygon& A, const Polygon& B) {
    // edge intersection
    size_t na = A.points.size();
    size_t nb = B.points.size();
    for (size_t i = 0; i < na; ++i) {
      Point a1 = A.points[i];
      Point a2 = A.points[(i + 1) % na];
      for (size_t j = 0; j < nb; ++j) {
        Point b1 = B.points[j];
        Point b2 = B.points[(j + 1) % nb];
        if (segmentsIntersect(a1, a2, b1, b2)) {
          return true;
        }
      }
    }
    // containment: A inside B?
    // Ray-casting for a point
    auto pointInPoly = [&](const Polygon& P,
      const Point& pt) {
        bool inside = false;
        size_t n = P.points.size();
        for (size_t i = 0, j = n - 1; i < n; _
