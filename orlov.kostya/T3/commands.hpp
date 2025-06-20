#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

#include "datastruct.hpp"

namespace orlov
{
    extern std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>> commandsList;
    void executeCommand(const std::vector<Polygon>&, std::istream&, std::ostream&);

    void calcAreaSum(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void countPolygons(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void findMinimum(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void findMaximum(const std::vector<Polygon>&, std::istream&, std::ostream&);

    int orientation(const Point& p, const Point& q, const Point& r);
    bool onSegment(const Point& p, const Point& q, const Point& r);
    bool checkIntersection(const Point& p1, const Point& q1, const Point& p2, const Point& q2);
    bool isPointInPolygon(const Point& point, const Polygon& polygon);
    bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2);
    void intersectPolygons(const std::vector<Polygon>&, std::istream&, std::ostream&);

    void checkInsideFrame(const std::vector<Polygon>&, std::istream&, std::ostream&);
}

#endif

