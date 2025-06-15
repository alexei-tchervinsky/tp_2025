#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <limits>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool Point::operator!=(const Point& other) const {
    return !(*this == other);
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    if (n < 3) return 0.0;
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      area += double(a.x) * b.y - double(b.x) * a.y;
    }
    return std::fabs(area) / 2.0;
  }

  // Проверка, является ли 4-вершинный полигон прямоугольником
  bool Polygon::isRectangle() const {
    size_t n = points.size();
    if (n != 4) return false;
    // По порядку точек. Проверяем 4 угла.
    auto dot = [](const Point& a, const Point& b, const Point& c) {
      // угол в b: векторы ba и bc
      int dx1 = a.x - b.x;
      int dy1 = a.y - b.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      return dx1 * dx2 + dy1 * dy2;
      };
    for (size_t i = 0; i < 4; ++i) {
      const Point& a = points[(i + 3) % 4];
      const Point& b = points[i];
      const Point& c = points[(i + 1) % 4];
      if (dot(a, b, c) != 0) return false;
    }
    return true;
  }

  // Проверка наличия хотя бы одного прямого угла
  bool Polygon::hasRightAngle() const {
    size_t n = points.size();
    if (n < 3) return false;
    auto dot = [](const Point& a, const Point& b, const Point& c) {
      int dx1 = a.x - b.x;
      int dy1 = a.y - b.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      return dx1 * dx2 + dy1 * dy2;
      };
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[(i + n - 1) % n];
      const Point& b = points[i];
      const Point& c = points[(i + 1) % n];
      if (dot(a, b, c) == 0) {
        return true;
      }
    }
    return false;
  }

  // Проверка перестановки порядка вершин (циклический сдвиг или обратный)
  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    if (n == 0) return false;
    for (size_t shift = 0; shift < n; ++shift) {
      bool ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(i + shift) % n]) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
      ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(n + shift - i) % n]) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
    }
    return false;
  }

  // Проверка совпадения по наложению (без поворотов), т.е. смещение только
  bool Polygon::isSameByTranslation(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    if (n == 0) return false;
    // Для всех циклических сдвигов проверяем, что разность координат постоянна
    for (size_t shift = 0; shift < n; ++shift) {
      int dx = other.points[shift].x - points[0].x;
      int dy = other.points[shift].y - points[0].y;
      bool ok = true;
      for (size_t i = 0; i < n; ++i) {
        const Point& p1 = points[i];
        const Point& p2 = other.points[(i + shift) % n];
        if (p1.x + dx != p2.x || p1.y + dy != p2.y) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
    }
    return false;
  }

  std::istream& operator>>(std::istream& in, Point& point) {
    char ch;
    in >> std::ws >> ch;
    if (!in || ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.x;
    if (!in) {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ch;
    if (!in || ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.y;
    if (!in) {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ch;
    if (!in || ch != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t sz;
    in >> sz;
    if (!in) return in;
    std::vector<Point> pts;
    pts.reserve(sz);
    Point pt;
    for (size_t i = 0; i < sz; ++i) {
      if (!(in >> pt)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      pts.push_back(pt);
    }
    polygon.points = std::move(pts);
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    out << polygon.points.size();
    for (const auto& pt : polygon.points) {
      out << " (" << pt.x << ";" << pt.y << ")";
    }
    return out;
  }

} // namespace prokopenko
