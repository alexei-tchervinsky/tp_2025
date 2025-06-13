#include "polygon.hpp"
#include <cmath>

namespace prokopenko {

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '\0';
    in >> c;
    if (in && c != dest.del) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Point& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    Point point;
    in >> DelimiterIO{ '(' };
    in >> point.x;
    in >> DelimiterIO{ ';' };
    in >> point.y;
    in >> DelimiterIO{ ')' };
    dest = point;
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    Polygon polygon;
    std::size_t vertexes = 0;
    if (!(in >> vertexes)) {
      in.setstate(std::ios::failbit);
      return in;
    }
    Point pt;
    for (std::size_t i = 0; i < vertexes; ++i) {
      in >> pt;
      if (in) polygon.push_back(pt);
    }
    if (polygon.size() != vertexes || vertexes < 3) {
      in.setstate(std::ios::failbit);
    }
    dest = polygon;
    return in;
  }

  double getArea(const Polygon& polygon) {
    double area = 0.0;
    for (std::size_t i = 0; i < polygon.size(); ++i) {
      const Point& a = polygon[i];
      const Point& b = polygon[(i + 1) % polygon.size()];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::fabs(area) / 2.0;
  }

}
