#include "polygon.hpp"
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  double Polygon::getArea() const {
    if (points.size() < 3) return 0.0;
    long long area = 0;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      area += static_cast<long long>(points[i].x) * points[(i + 1) % n].y;
      area -= static_cast<long long>(points[(i + 1) % n].x) * points[i].y;
    }
    return std::fabs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    size_t n = points.size();
    if (n < 3) return false;
    for (size_t i = 0; i < n; ++i) {
      const auto& a = points[i];
      const auto& b = points[(i + 1) % n];
      const auto& c = points[(i + 2) % n];
      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      if (dx1 * dx2 + dy1 * dy2 == 0) {
        return true;
      }
    }
    return false;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    std::vector<Point> a = points, b = other.points;
    for (size_t shift = 0; shift < b.size(); ++shift) {
      bool ok = true;
      for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].x != b[(i + shift) % b.size()].x ||
          a[i].y != b[(i + shift) % b.size()].y) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
      std::reverse(b.begin(), b.end());
      ok = true;
      for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].x != b[(i + shift) % b.size()].x ||
          a[i].y != b[(i + shift) % b.size()].y) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
      std::reverse(b.begin(), b.end());
    }
    return false;
  }

  std::istream& operator>>(std::istream& in, Polygon& p) {
    p.points.clear();
    size_t n;
    if (!(in >> n) || n < 3) return in.setstate(std::ios::failbit), in;
    std::string token;
    for (size_t i = 0; i < n; ++i) {
      if (!(in >> token)) return in.setstate(std::ios::failbit), in;
      if (token.front() != '(' || token.back() != ')') return in.setstate(std::ios::failbit), in;
      size_t semicolon = token.find(';');
      if (semicolon == std::string::npos) return in.setstate(std::ios::failbit), in;
      std::string xs = token.substr(1, semicolon - 1);
      std::string ys = token.substr(semicolon + 1, token.size() - semicolon - 2);
      try {
        int x = std::stoi(xs);
        int y = std::stoi(ys);
        p.points.push_back({ x, y });
      }
      catch (...) {
        return in.setstate(std::ios::failbit), in;
      }
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& p) {
    out << p.points.size();
    for (const auto& pt : p.points) {
      out << " (" << pt.x << ";" << pt.y << ")";
    }
    return out;
  }

} // namespace prokopenko
