#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP

#include "polygon.hpp"
#include <string>

double computeArea(const Polygon& poly);
bool doSegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);
bool doPolygonsIntersect(const Polygon& a, const Polygon& b);
bool parsePolygon(const std::string& str, Polygon& poly);

#endif // COMPUTATIONS_HPP