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

  static bool isDuplicate(const std::vector<Polygon>& seen,
    const Polygon& p) {
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
        if (a > EPS && (p.points.size() % 2 == (param == "EVEN" ? 0 : 1))) {
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
      double minA = -1;
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
      bool found = false;
      for (const auto& p : polys) {
        if (p.getArea() > EPS) {
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
      if (p.isRight() && p.getArea() > EPS) ++count;
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

  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    double a0 = ref.getArea();
    if (a0 < EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
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
    double a0 = ref.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < a0) ++count;
    }
    out << count << '\n';
  }

  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = ref.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a > a0) ++count;
    }
    out << count << '\n';
  }

  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = ref.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      if (std::fabs(p.getArea() - a0) < EPS) ++count;
    }
    out << count << '\n';
  }

  void MaxSeq(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t best = 0, current = 0;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) {
        ++current;
        if (current > best) best = current;
      }
      else {
        current = 0;
      }
    }
    out << best << '\n';
  }

  void RmEcho(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    bool seen = false;
    for (const auto& p : polys) {
      if (p.isPermOf(ref)) {
        if (seen) ++count;
        else seen = true;
      }
      else {
        seen = false;
      }
    }
    out << count << '\n';
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
    double a0 = ref.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t count = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < a0) ++count;
    }
    out << count << '\n';
  }

  void InFrame(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    int minX = INT_MAX, maxX = INT_MIN;
    int minY = INT_MAX, maxY = INT_MIN;

    for (const auto& poly : polys) {
      for (const auto& pt : poly.points) {
        minX = std::min(minX, pt.x);
        maxX = std::max(maxX, pt.x);
        minY = std::min(minY, pt.y);
        maxY = std::max(maxY, pt.y);
      }
    }

    for (const auto& pt : ref.points) {
      if (pt.x < minX || pt.x > maxX || pt.y < minY || pt.y > maxY) {
        out << "<FALSE>\n";
        return;
      }
    }
    out << "<TRUE>\n";
  }

  void Intersections(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon ref;
    if (!(std::cin >> ref)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    size_t count = 0;
    for (const auto& p : polys) {
      if (p.intersects(ref)) ++count;
    }
    out << count << '\n';
  }

} // namespace prokopenko
