#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <set>

namespace prokopenko {

  constexpr double EPSILON = 1e-6;

  double sumAreas(const std::vector<Polygon>& polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double acc, const Polygon& p) {
        return acc + getArea(p);
      });
  }

  bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(getArea(a) - getArea(b)) < EPSILON;
  }

  void Area(const std::vector<Polygon>& polygons, std::ostream& out) {
    out << std::fixed << std::setprecision(1) << sumAreas(polygons) << '\n';
  }

  void Max(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "<EMPTY DATASET>\n";
      return;
    }
    auto max_it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
      });
    out << std::fixed << std::setprecision(1) << getArea(*max_it) << '\n';
  }

  void Min(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "<EMPTY DATASET>\n";
      return;
    }
    auto min_it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
      });
    out << std::fixed << std::setprecision(1) << getArea(*min_it) << '\n';
  }

  void Mean(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "<EMPTY DATASET>\n";
      return;
    }
    double mean = sumAreas(polygons) / polygons.size();
    out << std::fixed << std::setprecision(1) << mean << '\n';
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "0\n";
      return;
    }
    const Polygon& first = polygons.front();
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [&first](const Polygon& p) {
        return equalArea(first, p);
      });
    out << count << '\n';
  }

  double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
  }

  Point vectorBetween(const Point& from, const Point& to) {
    return { to.x - from.x, to.y - from.y };
  }

  bool isRightAngle(const Point& a, const Point& b, const Point& c) {
    Point ab = vectorBetween(b, a);
    Point cb = vectorBetween(b, c);
    return std::fabs(dot(ab, cb)) < EPSILON;
  }

  bool isRectangle(const Polygon& polygon) {
    if (polygon.size() != 4) return false;
    const Point& p0 = polygon[0];
    const Point& p1 = polygon[1];
    const Point& p2 = polygon[2];
    const Point& p3 = polygon[3];
    return isRightAngle(p0, p1, p2) &&
      isRightAngle(p1, p2, p3) &&
      isRightAngle(p2, p3, p0) &&
      isRightAngle(p3, p0, p1);
  }

  void Right(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    out << count << '\n';
  }

  bool arePermutations(const Polygon& a, const Polygon& b) {
    if (a.size() != b.size()) return false;
    auto a_sorted = a;
    auto b_sorted = b;
    std::sort(a_sorted.begin(), a_sorted.end());
    std::sort(b_sorted.begin(), b_sorted.end());
    return a_sorted == b_sorted;
  }

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "0\n";
      return;
    }
    const Polygon& first = polygons.front();
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [&first](const Polygon& p) {
        return arePermutations(first, p);
      });
    out << count << '\n';
  }

  void Less(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "0\n";
      return;
    }
    const Polygon& first = polygons.front();
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [&first](const Polygon& p) {
        return getArea(p) < getArea(first);
      });
    out << count << '\n';
  }

  void More(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "0\n";
      return;
    }
    const Polygon& first = polygons.front();
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [&first](const Polygon& p) {
        return getArea(p) > getArea(first);
      });
    out << count << '\n';
  }

  void Equal(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << "0\n";
      return;
    }
    const Polygon& first = polygons.front();
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [&first](const Polygon& p) {
        return equalArea(p, first);
      });
    out << count << '\n';
  }

}
