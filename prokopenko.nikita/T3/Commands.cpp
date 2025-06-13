#include "commands.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

// SAME: подсчёт фигур, совпадающих по точному порядку вершин
void doSAME(const Polygon& poly, const std::vector<Polygon>& shapes) {
  int count = 0;
  for (const auto& shp : shapes) {
    if (shp == poly) {
      count++;
    }
  }
  std::cout << "SAME " << poly << " " << count << std::endl;
}

// PERMS: подсчёт фигур, имеющих ту же совокупность вершин (порядок не важен)
void doPERMS(const Polygon& poly, const std::vector<Polygon>& shapes) {
  // Собираем упорядоченный список точек переданной фигуры
  std::vector<std::pair<int, int>> pts1;
  for (const auto& p : poly.points) {
    pts1.emplace_back(p.x, p.y);
  }
  std::sort(pts1.begin(), pts1.end());
  int count = 0;
  for (const auto& shp : shapes) {
    if (shp.points.size() != poly.points.size()) {
      continue;
    }
    std::vector<std::pair<int, int>> pts2;
    for (const auto& p : shp.points) {
      pts2.emplace_back(p.x, p.y);
    }
    std::sort(pts2.begin(), pts2.end());
    if (pts1 == pts2) {
      count++;
    }
  }
  std::cout << "PERMS " << poly << " " << count << std::endl;
}

// EQUAL: подсчёт фигур с одинаковой площадью (с учётом погрешности)
void doEQUAL(const Polygon& poly, const std::vector<Polygon>& shapes) {
  double area = poly.getArea();
  int count = 0;
  for (const auto& shp : shapes) {
    double a = shp.getArea();
    if (std::fabs(a - area) <= 1e-6) {
      count++;
    }
  }
  std::cout << "EQUAL " << poly << " " << count << std::endl;
}

// COUNT: подсчёт фигур с тем же количеством вершин
void doCOUNT(const Polygon& poly, const std::vector<Polygon>& shapes) {
  int n = poly.points.size();
  int count = 0;
  for (const auto& shp : shapes) {
    if ((int)shp.points.size() == n) {
      count++;
    }
  }
  std::cout << "COUNT " << poly << " " << count << std::endl;
}
