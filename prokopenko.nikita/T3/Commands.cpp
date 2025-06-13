#include "commands.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace prokopenko {

  bool isRightTriangle(const Point& a, const Point& b, const Point& c) {
    auto square = [](const Point& p1, const Point& p2) {
      int dx = p2.x - p1.x;
      int dy = p2.y - p1.y;
      return dx * dx + dy * dy;
      };

    int ab2 = square(a, b);
    int bc2 = square(b, c);
    int ca2 = square(c, a);

    return ab2 + bc2 == ca2 || ab2 + ca2 == bc2 || bc2 + ca2 == ab2;
  }

  void Area(const std::vector<Polygon>& polygons, std::ostream& out) {
    double total = 0.0;
    for (const Polygon& p : polygons) {
      total += p.getArea();
    }
    out << total << '\n';
  }

  void Max(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << 0 << '\n';
      return;
    }
    size_t maxSize = 0;
    for (const Polygon& p : polygons) {
      maxSize = std::max(maxSize, p.size());
    }
    out << maxSize << '\n';
  }

  void Min(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << 0 << '\n';
      return;
    }
    size_t minSize = polygons.front().size();
    for (const Polygon& p : polygons) {
      minSize = std::min(minSize, p.size());
    }
    out << minSize << '\n';
  }

  void Mean(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) {
      out << 0 << '\n';
      return;
    }
    size_t total = 0;
    for (const Polygon& p : polygons) {
      total += p.size();
    }
    double avg = static_cast<double>(total) / polygons.size();
    out << avg << '\n';
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out) {
    for (size_t i = 0; i < polygons.size(); ++i) {
      for (size_t j = i + 1; j < polygons.size(); ++j) {
        if (polygons[i] == polygons[j]) {
          out << polygons[i] << '\n';
        }
      }
    }
  }

  void Right(const std::vector<Polygon>& polygons, std::ostream& out) {
    for (const Polygon& p : polygons) {
      for (size_t i = 0; i + 2 < p.size(); ++i) {
        if (isRightTriangle(p[i], p[i + 1], p[i + 2])) {
          out << p << '\n';
          break;
        }
      }
    }
  }

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out) {
    for (size_t i = 0; i < polygons.size(); ++i) {
      for (size_t j = i + 1; j < polygons.size(); ++j) {
        if (polygons[i].isPermutation(polygons[j])) {
          out << polygons[i] << '\n';
        }
      }
    }
  }

  void Less(const std::vector<Polygon>& polygons, std::ostream& out) {
    size_t n;
    std::cin >> n;
    for (const Polygon& p : polygons) {
      if (p.size() < n) {
        out << p << '\n';
      }
    }
  }

  void More(const std::vector<Polygon>& polygons, std::ostream& out) {
    size_t n;
    std::cin >> n;
    for (const Polygon& p : polygons) {
      if (p.size() > n) {
        out << p << '\n';
      }
    }
  }

  void Equal(const std::vector<Polygon>& polygons, std::ostream& out) {
    size_t n;
    std::cin >> n;
    for (const Polygon& p : polygons) {
      if (p.size() == n) {
        out << p << '\n';
      }
    }
  }

  // 🔽 🔽 🔽 Новые команды COUNT добавлены ниже 🔽 🔽 🔽

  void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) {
        return p.size() % 2 == 1;
      });
    out << count << '\n';
  }

  void CountEven(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) {
        return p.size() % 2 == 0;
      });
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polygons, std::ostream& out, std::size_t n) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [n](const Polygon& p) {
        return p.size() == n;
      });
    out << count << '\n';
  }

}
