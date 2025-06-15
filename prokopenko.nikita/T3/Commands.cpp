#include "commands.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <limits>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  // утилиты

  // проверка, все ли символы цифры
  static bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    return std::all_of(s.begin(), s.end(), ::isdigit);
  }

  // подсчёт уникальных по перестановке фигур из polys
  static size_t countUniqueByPerm(const std::vector<Polygon>& polys, std::function<bool(const Polygon&)> filter) {
    std::vector<Polygon> uniq;
    for (const auto& p : polys) {
      if (!filter(p)) continue;
      bool found = false;
      for (auto& q : uniq) {
        if (p.isPermOf(q)) { found = true; break; }
      }
      if (!found) uniq.push_back(p);
    }
    return uniq.size();
  }

  // проверка попадания точки в ось-прямоугольник [minX,maxX]x[minY,maxY]
  static bool pointInRect(const Point& pt, int minX, int maxX, int minY, int maxY) {
    return pt.x >= minX && pt.x <= maxX && pt.y >= minY && pt.y <= maxY;
  }

  // ориентация трех точек для пересечения отрезков
  static int orient(const Point& a, const Point& b, const Point& c) {
    long long v = (long long)(b.y - a.y) * (c.x - b.x) - (long long)(b.x - a.x) * (c.y - b.y);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
  }
  static bool onSegment(const Point& a, const Point& b, const Point& p) {
    return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)
      && std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
  }
  // пересекаются ли отрезки ab и cd
  static bool segIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    int o1 = orient(a, b, c);
    int o2 = orient(a, b, d);
    int o3 = orient(c, d, a);
    int o4 = orient(c, d, b);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(a, b, c)) return true;
    if (o2 == 0 && onSegment(a, b, d)) return true;
    if (o3 == 0 && onSegment(c, d, a)) return true;
    if (o4 == 0 && onSegment(c, d, b)) return true;
    return false;
  }
  // точка-in-полигон (лучевой метод)
  static bool pointInPoly(const Polygon& poly, const Point& pt) {
    bool inside = false;
    size_t n = poly.points.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
      const Point& pi = poly.points[i];
      const Point& pj = poly.points[j];
      if (((pi.y > pt.y) != (pj.y > pt.y)) &&
        (pt.x < (long double)(pj.x - pi.x) * (pt.y - pi.y) / (pj.y - pi.y) + pi.x)) {
        inside = !inside;
      }
    }
    return inside;
  }

  // проверка пересечения полигонов p и q
  static bool polyIntersect(const Polygon& p, const Polygon& q) {
    size_t np = p.points.size();
    size_t nq = q.points.size();
    if (np < 3 || nq < 3) return false;
    // проверка пересечения рёбер
    for (size_t i = 0; i < np; ++i) {
      Point a = p.points[i];
      Point b = p.points[(i + 1) % np];
      for (size_t j = 0; j < nq; ++j) {
        Point c = q.points[j];
        Point d = q.points[(j + 1) % nq];
        if (segIntersect(a, b, c, d)) return true;
      }
    }
    // проверяем, лежит ли точка одного внутри другого
    if (pointInPoly(p, q.points[0])) return true;
    if (pointInPoly(q, p.points[0])) return true;
    return false;
  }

  // AREA
  void Area(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN" || param == "ODD") {
      bool wantOdd = (param == "ODD");
      double sum = 0.0;
      for (auto& p : polys) {
        double a = p.getArea();
        if (a <= EPS) continue;
        if ((p.points.size() % 2 == 1) == wantOdd) {
          sum += a;
        }
      }
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (param == "MEAN") {
      // требуется хотя бы одна фигура с area>0
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
        out << std::fixed << std::setprecision(1) << (sum / cnt) << '\n';
      }
    }
    else if (isNumber(param)) {
      size_t n = 0;
      try { n = std::stoul(param); }
      catch (...) { out << "<INVALID COMMAND>\n"; return; }
      if (n < 3) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = 0.0;
      for (auto& p : polys) {
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

  // MAX
  void Max(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = -std::numeric_limits<double>::infinity();
      bool found = false;
      for (auto& p : polys) {
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
      for (auto& p : polys) {
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

  // MIN
  void Min(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = std::numeric_limits<double>::infinity();
      bool found = false;
      for (auto& p : polys) {
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
      for (auto& p : polys) {
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

  // MEAN (синоним AREA MEAN)
  void Mean(std::vector<Polygon>& polys, std::ostream& out) {
    // просто переиспользуем Area с параметром MEAN
    std::string dummy = "MEAN";
    // вручную вызываем Area
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
      out << std::fixed << std::setprecision(1) << (sum / cnt) << '\n';
    }
  }

  // COUNT
  void Count(std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN") {
      size_t cnt = countUniqueByPerm(polys, [](const Polygon& p) {
        return p.getArea() > EPS && (p.points.size() % 2 == 0);
        });
      out << cnt << '\n';
    }
    else if (param == "ODD") {
      size_t cnt = countUniqueByPerm(polys, [](const Polygon& p) {
        return p.getArea() > EPS && (p.points.size() % 2 == 1);
        });
      out << cnt << '\n';
    }
    else if (isNumber(param)) {
      size_t n = 0;
      try { n = std::stoul(param); }
      catch (...) { out << "<INVALID COMMAND>\n"; return; }
      if (n < 3) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      size_t cnt = countUniqueByPerm(polys, [n](const Polygon& p) {
        return p.getArea() > EPS && p.points.size() == n;
        });
      out << cnt << '\n';
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
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (auto& p : polys) {
      if (p.isPermOf(pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // MAXSEQ <Polygon>
  void MaxSeq(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t best = 0;
    size_t cur = 0;
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
  void RmEcho(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t removed = 0;
    // удаляем подряд идущие дубликаты pattern: оставляем первый, удаляем последующие
    std::vector<Polygon> result;
    size_t i = 0;
    while (i < polys.size()) {
      if (polys[i].isPermOf(pattern)) {
        // встречаем начало участка?
        // добавляем эту первую
        result.push_back(polys[i]);
        size_t j = i + 1;
        while (j < polys.size() && polys[j].isPermOf(pattern)) {
          ++removed;
          ++j;
        }
        i = j;
      }
      else {
        result.push_back(polys[i]);
        ++i;
      }
    }
    polys.swap(result);
    out << removed << '\n';
  }

  // ECHO <Polygon>
  void Echo(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t added = 0;
    // дублируем каждое вхождение pattern: вставляем копию сразу после
    for (size_t i = 0; i < polys.size(); ++i) {
      if (polys[i].isPermOf(pattern)) {
        polys.insert(polys.begin() + i + 1, polys[i]);
        ++added;
        ++i; // пропустить вставленный
      }
    }
    out << added << '\n';
  }

  // LESSAREA <Polygon>
  void LessArea(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (auto& p : polys) {
      double a = p.getArea();
      if (a > EPS && a < a0) ++cnt;
    }
    out << cnt << '\n';
  }

  // INFRAME <Polygon>
  void InFrame(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (polys.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    // вычисляем bounding rectangle по всем poly в коллекции
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();
    for (auto& poly : polys) {
      for (auto& pt : poly.points) {
        if (pt.x < minX) minX = pt.x;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.y > maxY) maxY = pt.y;
      }
    }
    bool ok = true;
    for (auto& pt : pattern.points) {
      if (!pointInRect(pt, minX, maxX, minY, maxY)) {
        ok = false;
        break;
      }
    }
    out << (ok ? "<TRUE>\n" : "<FALSE>\n");
  }

  // INTERSECTIONS <Polygon>
  void Intersections(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t cnt = 0;
    for (auto& p : polys) {
      if (polyIntersect(p, pattern)) ++cnt;
    }
    out << cnt << '\n';
  }

  // SAME <Polygon>: "совместимых наложением (без поворотов)"
  // Т.е. совпадают по форме и последовательность, допускается только перевод: циклический сдвиг, но не зеркалирование
  void Same(std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "0\n";
      return;
    }
    size_t n = pattern.points.size();
    size_t cnt = 0;
    for (auto& p : polys) {
      if (p.points.size() != n) continue;
      // проверка на совпадение по циклическому сдвигу (только прямой порядок, без обратного)
      bool match = false;
      for (size_t shift = 0; shift < n; ++shift) {
        bool ok = true;
        for (size_t i = 0; i < n; ++i) {
          int dx = p.points[(i + shift) % n].x - pattern.points[i].x;
          int dy = p.points[(i + shift) % n].y - pattern.points[i].y;
          // при переводе все смещения одинаковы? здесь только проверяем равенство: pattern points + (dx,dy) == p sequence
          // но dx,dy могут быть любыми; достаточно проверить, что разница p - pattern постоянна:
          if (i == 0) {
            // сохраняем смещение
          }
          else {
            // сравним смещение текущ и предыдущ? проще: сравнить относительные разницы pattern->pattern равны p->p
          }
          // Альтернативный метод: вычислить dx0,dy0 для i=0, затем проверить для всех i:
          ;
        }
        // проще: для смещения: dx0 = p.points[shift].x - pattern.points[0].x; dy0 аналог
        int dx0 = p.points[shift].x - pattern.points[0].x;
        int dy0 = p.points[shift].y - pattern.points[0].y;
      ok:
        ;
        bool ok2 = true;
        for (size_t i = 0; i < n; ++i) {
          size_t idx = (i + shift) % n;
          if (p.points[idx].x != pattern.points[i].x + dx0 ||
            p.points[idx].y != pattern.points[i].y + dy0) {
            ok2 = false;
            break;
          }
        }
        if (ok2) { match = true; break; }
      }
      if (match) ++cnt;
    }
    out << cnt << '\n';
  }

  // RECTS: подсчитать количество прямоугольников (любых ориентированных): polygon.size()==4 и все углы прямые
  void Rects(std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (auto& p : polys) {
      if (p.points.size() != 4) continue;
      bool ok = true;
      for (size_t i = 0; i < 4; ++i) {
        const Point& a = p.points[i];
        const Point& b = p.points[(i + 1) % 4];
        const Point& c = p.points[(i + 2) % 4];
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

  // RIGHTSHAPES: подсчитать количество фигур, содержащих хотя бы один прямой угол
  void RightShapes(std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (auto& p : polys) {
      if (p.isRight()) ++cnt;
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
