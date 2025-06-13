#include "commands.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include <vector>
#include <cmath>
#include <iostream>

// Порог для сравнения площадей (исключение вырожденных полигонов)
static const double EPS = 1e-9;

// Функция сравнения двух полигонов: совпадение всех вершин
static bool polygonsEqual(const Polygon& p1, const Polygon& p2) {
  if (p1.getNumVertices() != p2.getNumVertices()) return false;
  int n = p1.getNumVertices();
  for (int i = 0; i < n; ++i) {
    const Point& a = p1.getVertex(i);
    const Point& b = p2.getVertex(i);
    if (std::fabs(a.x - b.x) > EPS || std::fabs(a.y - b.y) > EPS) {
      return false;
    }
  }
  return true;
}

void ODD() {
  // Собираем уникальные непустые полигоны
  std::vector<Polygon*> uniquePolys;
  for (auto shape : shapes) {
    Polygon* poly = dynamic_cast<Polygon*>(shape);
    if (!poly) continue;
    if (poly->area() <= EPS) continue;
    bool isDup = false;
    for (auto u : uniquePolys) {
      if (polygonsEqual(*u, *poly)) { isDup = true; break; }
    }
    if (!isDup) uniquePolys.push_back(poly);
  }
  // Подсчитываем полигоны с нечётным числом вершин
  int count = 0;
  for (auto poly : uniquePolys) {
    if (poly->getNumVertices() % 2 == 1) {
      ++count;
    }
  }
  std::cout << count << std::endl;
}

void EVEN() {
  // Собираем уникальные непустые полигоны
  std::vector<Polygon*> uniquePolys;
  for (auto shape : shapes) {
    Polygon* poly = dynamic_cast<Polygon*>(shape);
    if (!poly) continue;
    if (poly->area() <= EPS) continue;
    bool isDup = false;
    for (auto u : uniquePolys) {
      if (polygonsEqual(*u, *poly)) { isDup = true; break; }
    }
    if (!isDup) uniquePolys.push_back(poly);
  }
  // Подсчитываем полигоны с чётным числом вершин
  int count = 0;
  for (auto poly : uniquePolys) {
    if (poly->getNumVertices() % 2 == 0) {
      ++count;
    }
  }
  std::cout << count << std::endl;
}

void N(int N) {
  // Собираем уникальные непустые полигоны
  std::vector<Polygon*> uniquePolys;
  for (auto shape : shapes) {
    Polygon* poly = dynamic_cast<Polygon*>(shape);
    if (!poly) continue;
    if (poly->area() <= EPS) continue;
    bool isDup = false;
    for (auto u : uniquePolys) {
      if (polygonsEqual(*u, *poly)) { isDup = true; break; }
    }
    if (!isDup) uniquePolys.push_back(poly);
  }
  // Подсчитываем полигоны с числом вершин == N
  int count = 0;
  for (auto poly : uniquePolys) {
    if (poly->getNumVertices() == N) {
      ++count;
    }
  }
  std::cout << count << std::endl;
}
