#include "polygon.hpp"
#include <cmath>

namespace prokopenko {

  // Ввод точки формата "(x;y)"
  std::istream& operator>>(std::istream& in, Point& point)
  {
    char ch = 0;
    in >> std::ws >> ch;
    if (!in || ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.x >> ch;
    if (!in || ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.y >> ch;
    if (!in || ch != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  // Ввод полигона: сначала число вершин, затем точки
  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    size_t sz = 0;
    in >> sz;
    if (!in) {
      return in;
    }
    std::vector<Point> temp;
    temp.reserve(sz);
    for (size_t i = 0; i < sz; ++i) {
      Point pt;
      in >> pt;
      if (!in) {
        // Ошибка чтения точки
        in.setstate(std::ios::failbit);
        return in;
      }
      temp.push_back(pt);
    }
    if (sz < 3 || temp.size() != sz) {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.points = std::move(temp);
    return in;
  }

  // Вывод точки
  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    out << "(" << point.x << ";" << point.y << ")";
    return out;
  }

  // Вывод полигона: количество точек + каждую через пробел
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
  {
    out << polygon.points.size();
    for (const auto& pt : polygon.points) {
      out << " " << pt;
    }
    return out;
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    if (n < 3) return 0.0;
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      area += static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
    }
    return std::abs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    size_t n = points.size();
    if (n < 3) return false;
    // Проверяем, есть ли хотя бы один прямой угол
    for (size_t i = 0; i < n; ++i) {
      const Point& prev = points[(i + n - 1) % n];
      const Point& cur = points[i];
      const Point& next = points[(i + 1) % n];
      int dx1 = cur.x - prev.x;
      int dy1 = cur.y - prev.y;
      int dx2 = next.x - cur.x;
      int dy2 = next.y - cur.y;
      if ((dx1 * dx2 + dy1 * dy2) == 0) {
        return true;
      }
    }
    return false;
  }

  bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    if (n == 0) return true;
    // Проверяем все циклические сдвиги (CW и CCW)
    for (size_t offset = 0; offset < n; ++offset) {
      bool okCW = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(i + offset) % n]) {
          okCW = false;
          break;
        }
      }
      if (okCW) return true;

      bool okCCW = true;
      for (size_t i = 0; i < n; ++i) {
        size_t idx = (offset + n - i) % n;
        if (points[i] != other.points[idx]) {
          okCCW = false;
          break;
        }
      }
      if (okCCW) return true;
    }
    return false;
  }

} // namespace prokopenko
