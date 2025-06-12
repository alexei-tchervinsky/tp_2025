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

    int orientation(Point p, Point q, Point r);
    bool onSegment(Point p, Point q, Point r);
    bool checkIntersection(Point p1, Point q1, Point p2, Point q2);
    bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2);
    void intersectPolygons(const std::vector<Polygon>&, std::istream&, std::ostream&);

    void checkInsideFrame(const std::vector<Polygon>&, std::istream&, std::ostream&);
}

#endif

