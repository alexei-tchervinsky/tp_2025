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

  // проверка одинаковости по перестановке
  static bool isDuplicate(const std::vector<Polygon>& seen,
    const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return true;
    }
    return false;
  }

  // AREA ...
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
        if (a > EPS) { sum += a; ++cnt; }
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

  // MAX ...
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

  // MIN ...
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

  // Mean (без аргумента) – тот же, что и AREA MEAN
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
  void CountN(const std::vector<Polygon>& polys, std::ostream& out,
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

  // LESS <Polygon>  (подсчёт area<pattern.area)
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

  // EQUAL <Polygon> (area equal)
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
    // коллекция неизменяемая, но возвращаем число удалённых из гипотетической
    size_t removed = 0;
    bool in_seq = false;
    size_t seq_count = 0;
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        if (!in_seq) {
          in_seq = true;
          seq_count = 1;
        }
        else {
          ++seq_count;
          ++removed;
        }
      }
      else {
        in_seq = false;
        seq_count = 0;
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
    // гипотетически вставляем, но не меняем исходный вектор
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
    // вычислить bounding box всех точек в polys
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

  // пересечение отрезков
  static bool segmentsIntersect(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4) {
    auto orient = [](int ax, int ay, int bx, int by,
      int cx, int cy) {
        long long v = (long long)(bx - ax) * (cy - ay)
          - (long long)(by - ay) * (cx - ax);
        if (v > 0) return 1;
        if (v < 0) return -1;
        return 0;
      };
    auto onSeg = [](int ax, int ay, int bx, int by, int cx, int cy) {
      return std::min(ax, bx) <= cx && cx <= std::max(ax, bx)
        && std::min(ay, by) <= cy && cy <= s
