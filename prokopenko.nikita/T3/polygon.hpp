#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include <cmath>

namespace prokopenko {

  struct Point {
    int x;
    int y;
    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
      return !(*this == other);
    }
  };

  struct Polygon {
    std::vector<Point> points;

    double getArea() const {
      double area = 0.0;
      size_t n = points.size();
      for (size_t i = 0; i < n; ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % n];
        area += (a.x * b.y - b.x * a.y);
      }
      return std::fabs(area) / 2.0;
    }

    bool isRight() const {
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
        if (dx1 * dx2 + dy1 * dy2 == 0) {
          return true;
        }
      }
      return false;
    }

    bool isPermOf(const Polygon& other) const {
      if (points.size() != other.points.size()) return false;
      size_t n = points.size();
      for (size_t shift = 0; shift < n; ++shift) {
        bool okCW = true;
        for (size_t i = 0; i < n; ++i) {
          if (points[i] != other.points[(i + shift) % n]) {
            okCW = false;
            break;
          }
        }
        if (okCW) return true;
        bool okCCW = true;
        for (size_t i = 0; i < n; ++i) {
          if (points[i] != other.points[(n + shift - i) % n]) {
            okCCW = false;
            break;
          }
        }
        if (okCCW) return true;
      }
      return false;
    }
  };

  std::istream& operator>>(std::istream& in, Point& point) {
    char ch = 0;
    in >> std::ws >> ch;
    if (ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.x >> ch;
    if (ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.y >> ch;
    if (ch != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t sz = 0;
    in >> sz;
    if (!in) return in;
    std::vector<Point> tmp;
    for (size_t i = 0; i < sz; ++i) {
      Point p;
      in >> p;
      if (!in) {
        return in;
      }
      tmp.push_back(p);
    }
    polygon.points = std::move(tmp);
    return in;
  }

} // namespace prokopenko

#endif // POLYGON_HPP
