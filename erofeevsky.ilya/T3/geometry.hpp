#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <iostream>
#include <vector>
#include <functional>

namespace erofick
{
//структура для чтения символа-разделителя с проверкой
  struct DelimiterChar
  {
    char expected;
  };
  std::istream & operator>>(std::istream& in, DelimiterChar&& exp);
//структура для чтения строки-разделителя с проверкой
  struct DelimiterString
  {
    const char * expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterString&& exp);
//точка с координатами x и y
  struct Point
  {
    int x;
    int y;
  };
//операторы для работы с точкой
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& lhs, const Point& rhs);
//полигон набор точек
  struct Polygon
  {
    std::vector< Point > points;
  };
//ф-ции для работы с полигоном
  double getPolygonArea(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  //проверка вхождения полигона в другой
  bool operator<=(const Polygon& lhs, const Polygon& rhs);
  //проверка на наличие прямых углов
  bool isRightAngle(const Polygon& polygon);
  //ф-ции для нахождения границ полигона
  int findMaxX(const Polygon& polygon);
  int findMaxY(const Polygon& polygon);
  int findMinX(const Polygon& polygon);
  int findMinY(const Polygon& polygon);
   //получение ограничивающего прямоугольника
  Polygon getBoundingBox(const std::vector< Polygon >& polygon);

  //функтор для вычисления площади полигона
  struct AreaPolygon
  {
    Point p1;//первая точка
    double operator()(double area, const Point& p2, const Point& p3);
  };

  //функтор проверки прямого угла между тремя точками
  struct accumulateRightAngle
  {
    Point p1;
    Point p2;
    bool operator()(const Point& p3);
  };

  //команды обработки полигонов
  void area(const std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
  void inframe(const std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
  void rmecho(std::vector< Polygon >& value,
     std::istream& in, std::ostream& out);
}

#endif
