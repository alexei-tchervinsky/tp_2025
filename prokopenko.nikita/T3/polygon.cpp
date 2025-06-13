#include "polygon.hpp"
#include <cmath>

// Вычисление площади многоугольника (формула шнурка)
double Polygon::getArea() const {
  double area = 0.0;
  int n = points.size();
  if (n < 3) return 0.0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    area += (double)points[i].x * points[j].y - (double)points[j].x * points[i].y;
  }
  return std::fabs(area) / 2.0;
}

// Сравнение фигур по набору вершин (последовательное сравнение)
bool operator==(const Polygon& a, const Polygon& b) {
  return a.points == b.points;
}

// Лексикографическое сравнение фигур (нужно для sort/unique)
bool operator<(const Polygon& a, const Polygon& b) {
  return a.points < b.points;
}

// Чтение полигона из потока (формат: n (x;y) (x;y) ...)
std::istream& operator>>(std::istream& is, Polygon& poly) {
  int n;
  if (!(is >> n)) {
    return is;
  }
  poly.points.clear();
  poly.points.reserve(n);
  char c;
  for (int i = 0; i < n; ++i) {
    if (!(is >> c) || c != '(') { is.setstate(std::ios::failbit); return is; }
    int x;
    if (!(is >> x)) { is.setstate(std::ios::failbit); return is; }
    if (!(is >> c) || c != ';') { is.setstate(std::ios::failbit); return is; }
    int y;
    if (!(is >> y)) { is.setstate(std::ios::failbit); return is; }
    if (!(is >> c) || c != ')') { is.setstate(std::ios::failbit); return is; }
    poly.points.push_back(Point{ x, y });
  }
  return is;
}

// Вывод полигона в поток (формат: n (x;y) (x;y) ...)
std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
  os << poly.points.size();
  for (const auto& p : poly.points) {
    os << " (" << p.x << ";" << p.y << ")";
  }
  return os;
}
