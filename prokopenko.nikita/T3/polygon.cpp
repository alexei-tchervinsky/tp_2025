#include "polygon.hpp"
#include <cmath>
#include <algorithm>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool Point::operator!=(const Point& other) const {
    return !(*this == other);
  }

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
        // чтение точки не удалось — установить fail и вернуть
        dest.clear();
        in.setstate(std::ios::failbit);
        return in;
      }
      temp.push_back(pt);
    }
    // проверяем: если меньше 3 вершин или некорректное число прочитано
    if (temp.size() != sz || sz < 3) {
      dest.clear();
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.points = std::move(temp);
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    out << "(" << point.x << ";" << point.y << ")";
    return out;
  }

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
    // Проверяем, есть ли хотя бы один угол прямой.
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
    // Пробуем все смещения по часовой и против часовой
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
        // (offset - i) может быть отрицательным, берем по модулю n:
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
