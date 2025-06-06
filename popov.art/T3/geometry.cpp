#include "geometry.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
namespace popov {
    bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2) {
        auto getProjections = [](const Polygon& poly, double nx, double ny) {
            double minProj = std::numeric_limits<double>::max();
            double maxProj = -std::numeric_limits<double>::max();
            for (const auto& p : poly.points) {
                double proj = p.x * nx + p.y * ny;
                minProj = std::min(minProj, proj);
                maxProj = std::max(maxProj, proj);
            }
            return std::make_pair(minProj, maxProj);
        };
        for (size_t i = 0; i < poly1.points.size(); i++) {
            const Point& p1 = poly1.points[i];
            const Point& p2 = poly1.points[(i + 1) % poly1.points.size()];
            double nx = -(p2.y - p1.y);
            double ny = p2.x - p1.x;
            auto [min1, max1] = getProjections(poly1, nx, ny);
            auto [min2, max2] = getProjections(poly2, nx, ny);
            if (max1 < min2 || max2 < min1) {
                return false;
            }
        }
        for (size_t i = 0; i < poly2.points.size(); i++) {
            const Point& p1 = poly2.points[i];
            const Point& p2 = poly2.points[(i + 1) % poly2.points.size()];
            double nx = -(p2.y - p1.y);
            double ny = p2.x - p1.x;
            auto [min1, max1] = getProjections(poly1, nx, ny);
            auto [min2, max2] = getProjections(poly2, nx, ny);
            if (max1 < min2 || max2 < min1) {
                return false;
            }
        }
        return true;
    }
std::istream& popov::operator>>(std::istream& in, DelimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& popov::operator>>(std::istream& in, DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    in >> DelimiterChar{ exp.expected[i] };
    ++i;
  }
  return in;
}
std::istream& popov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delChar = DelimiterChar;
  Point temp = { 0, 0 };
  in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >> delChar{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}
bool popov::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}
bool popov::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}
bool popov::operator<=(const Polygon& lhs, const Polygon& rhs)
{
  int innerMinX = findMinX(lhs);
  int innerMinY = findMinY(lhs);
  int innerMaxX = findMaxX(lhs);
  int innerMaxY = findMaxY(lhs);
  int outerMinX = findMinX(rhs);
  int outerMinY = findMinY(rhs);
  int outerMaxX = findMaxX(rhs);
  int outerMaxY = findMaxY(rhs);
  return (innerMinX >= outerMinX) && (innerMaxX <= outerMaxX) && (innerMinY >= outerMinY) && (innerMaxY <= outerMaxY);
}
std::istream& popov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countPoints = 0;
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  using input_iterator_t = std::istream_iterator< Point >;
  std::copy_n(input_iterator_t{ in }, (countPoints - 1), std::back_inserter(temp));
  if (in.peek() != '\n')
  {
    std::copy_n(input_iterator_t{ in }, 1, std::back_inserter(temp));
  }
  if (in && (temp.size() == countPoints) && ((in.peek() == '\n')))
  {
    polygon.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
double popov::AreaPolygon::operator()(double area, const Point& p2, const Point& p3)
{
  area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}
double popov::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AreaPolygon{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}
bool popov::isRightAngle(const Polygon& polygon)
{
  auto countAngle = accumulateRightAngle{ polygon.points[polygon.points.size() - 2],polygon.points[polygon.points.size() - 1] };
  return (std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngle) != polygon.points.cend());
}
bool popov::accumulateRightAngle::operator()(const Point& p3)
{
  Point vec1{ p2.x - p1.x, p2.y - p1.y };
  Point vec2{ p2.x - p3.x, p2.y - p3.y };
  p1 = p2;
  p2 = p3;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}
namespace {
  bool compareByX(const popov::Point& lhs, const popov::Point& rhs) { return lhs.x < rhs.x; }
  bool compareByY(const popov::Point& lhs, const popov::Point& rhs) { return lhs.y < rhs.y; }
  bool comparePolygonsByMaxX(const popov::Polygon& lhs, const popov::Polygon& rhs) { return findMaxX(lhs) < findMaxX(rhs); }
  bool comparePolygonsByMaxY(const popov::Polygon& lhs, const popov::Polygon& rhs) { return findMaxY(lhs) < findMaxY(rhs); }
  bool comparePolygonsByMinX(const popov::Polygon& lhs, const popov::Polygon& rhs) { return findMinX(lhs) < findMinX(rhs); }
  bool comparePolygonsByMinY(const popov::Polygon& lhs, const popov::Polygon& rhs) { return findMinY(lhs) < findMinY(rhs); }
}
int popov::findMaxX(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}
int popov::findMaxY(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}
int popov::findMinX(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}
int popov::findMinY(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}
popov::Polygon popov::getBoundingBox(const std::vector<Polygon>& polygon)
{
  int pointMaxX = findMaxX(*std::max_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMaxX));
  int pointMaxY = findMaxY(*std::max_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMaxY));
  int pointMinX = findMinX(*std::min_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMinX));
  int pointMinY = findMinY(*std::min_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMinY));
  std::vector< Point > res{ {pointMinX, pointMinY}, {pointMinX, pointMaxY}, {pointMaxX, pointMaxY}, {pointMaxX, pointMinY} };
  return Polygon{ res };
}
