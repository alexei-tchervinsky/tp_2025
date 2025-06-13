#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
      return !(*this == other);
    }
  };

  struct Polygon
  {
    std::vector<Point> points;

    double getArea() const {
      double area = 0.0;
      size_t n = points.size();
      for (size_t i = 0; i < n; ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % n];
        area += (a.x * b.y - b.x * a.y);
      }
      return std::abs(area) / 2.0;
    }
    bool isRight() const {
      // проверяем, является ли многоугольник «right» (каждые три подряд точки образуют прямой угол)
      size_t n = points.size();
      if (n < 3) return false;
      for (size_t i = 0; i < n; ++i) {
        const Point& a = points[(i + n - 1) % n];
        const Point& b = points[i];
        const Point& c = points[(i + 1) % n];
        int dx1 = a.x - b.x;
        int dy1 = a.y - b.y;
        int dx2 = c.x - b.x;
        int dy2 = c.y - b.y;
        if (dx1 * dx2 + dy1 * dy2 != 0) {
          return false;
        }
      }
      return true;
    }
    bool isPermOf(const Polygon& other) const {
      if (points.size() != other.points.size()) return false;
      size_t n = points.size();
      for (size_t offset = 0; offset < n; ++offset) {
        bool ok = true;
        // по часовой
        for (size_t i = 0; i < n; ++i) {
          if (points[i] != other.points[(i + offset) % n]) {
            ok = false;
            break;
          }
        }
        if (ok) return true;
        // против часовой
        ok = true;
        for (size_t i = 0; i < n; ++i) {
          if (points[i] != other.points[(n + offset - i) % n]) {
            ok = false;
            break;
          }
        }
        if (ok) return true;
      }
      return false;
    }
  };

  // Чтение Point из формата "(x;y)"
  std::istream& operator>>(std::istream& in, Point& point) {
    char ch;
    in >> std::ws >> ch;
    if (!in || ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (!(in >> point.x)) {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ch;
    if (!in || ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (!(in >> point.y)) {
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

  // Чтение Polygon: сначала size, затем size точек
  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t sz;
    std::streampos pos = in.tellg();
    if (!(in >> sz)) {
      // не число: откатываем
      in.clear();
      in.seekg(pos);
      in.setstate(std::ios::failbit);
      return in;
    }
    Polygon tmp;
    Point p;
    for (size_t i = 0; i < sz; ++i) {
      if (!(in >> p)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      tmp.points.push_back(p);
    }
    if (sz < 3 || tmp.points.size() != sz) {
      in.setstate(std::ios::failbit);
      return in;
    }
    polygon = std::move(tmp);
    return in;
  }

} // namespace prokopenko

#endif // POLYGON_HPP
