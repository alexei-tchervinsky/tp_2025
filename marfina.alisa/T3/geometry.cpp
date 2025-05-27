#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <string>
#include <limits>

std::istream& marfina::operator>>(std::istream& in, DelimiterChar&& exp)
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

std::istream& marfina::operator>>(std::istream& in, DelimiterString&& exp)
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

std::istream& marfina::operator>>(std::istream& in, Point& point)
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

bool marfina::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool marfina::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

bool marfina::operator<=(const Polygon& lhs, const Polygon& rhs)
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

std::istream& marfina::operator>>(std::istream& in, Polygon& polygon)
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

double marfina::AreaPolygon::operator()(double area, const Point& p2, const Point& p3)
{
  area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

double marfina::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AreaPolygon{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}

bool marfina::isRightAngle(const Polygon& polygon)
{
  auto countAngle = accumulateRightAngle{ polygon.points[polygon.points.size() - 2],polygon.points[polygon.points.size() - 1] };
  return (std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngle) != polygon.points.cend());
}

bool marfina::accumulateRightAngle::operator()(const Point& p3)
{
  Point vec1{ p2.x - p1.x, p2.y - p1.y };
  Point vec2{ p2.x - p3.x, p2.y - p3.y };
  p1 = p2;
  p2 = p3;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}

namespace {
  bool compareByX(const marfina::Point& lhs, const marfina::Point& rhs) { return lhs.x < rhs.x; }
  bool compareByY(const marfina::Point& lhs, const marfina::Point& rhs) { return lhs.y < rhs.y; }
  bool comparePolygonsByMaxX(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return findMaxX(lhs) < findMaxX(rhs); }
  bool comparePolygonsByMaxY(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return findMaxY(lhs) < findMaxY(rhs); }
  bool comparePolygonsByMinX(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return findMinX(lhs) < findMinX(rhs); }
  bool comparePolygonsByMinY(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return findMinY(lhs) < findMinY(rhs); }
}

int marfina::findMaxX(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

int marfina::findMaxY(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

int marfina::findMinX(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

int marfina::findMinY(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

marfina::Polygon marfina::getBoundingBox(const std::vector<Polygon>& polygon)
{
  int pointMaxX = findMaxX(*std::max_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMaxX));
  int pointMaxY = findMaxY(*std::max_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMaxY));
  int pointMinX = findMinX(*std::min_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMinX));
  int pointMinY = findMinY(*std::min_element(polygon.cbegin(), polygon.cend(), comparePolygonsByMinY));
  std::vector< Point > res{ {pointMinX, pointMinY}, {pointMinX, pointMaxY}, {pointMaxX, pointMaxY}, {pointMaxX, pointMinY} };
  return Polygon{ res };
}

namespace {
  bool isEven(const marfina::Polygon& polygon) { return (polygon.points.size() % 2 == 0); }
  bool isOdd(const marfina::Polygon& polygon) { return !(polygon.points.size() % 2 == 0); }
  bool isSize(const marfina::Polygon& polygon, size_t numPoints) { return (polygon.points.size() == numPoints); }
  bool comparatorPoints(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return lhs.points.size() < rhs.points.size(); }
  bool comparatorArea(const marfina::Polygon& lhs, const marfina::Polygon& rhs) { return getPolygonArea(lhs) < getPolygonArea(rhs); }
}

void marfina::area(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  iofmtguard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  std::vector< Polygon > polygons;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (value.empty())
    {
      throw std::logic_error("No polygons");
    }
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isOdd);
  }
  else
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("Wrong number");
    }
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isCorrectCount);
  }
  std::vector< double > area;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getPolygonArea);
  double res = std::accumulate(area.cbegin(), area.cend(), 0.0);
  if (argument == "MEAN")
  {
    out << res / value.size();
  }
  else
  {
    out << res;
  }
}

void marfina::max(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("No polygons");
  }
  else
  {
    if (argument == "AREA")
    {
      iofmtguard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::max_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("Wrong argument");
    }
  }
}

void marfina::min(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("Wrong number");
  }
  else
  {
    if (argument == "AREA")
    {
      iofmtguard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::min_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("Wrong argument");
    }
  }
}

void marfina::count(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(value.begin(), value.end(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(value.begin(), value.end(), isOdd);
  }
  else
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("Wrong number");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    out << std::count_if(value.begin(), value.end(), isCorrectCount);
  }
}

void marfina::rightshapes(const std::vector<Polygon>& value, std::ostream& out)
{
  using namespace std::placeholders;
  out << std::count_if(value.cbegin(), value.cend(), isRightAngle);
}

void marfina::inframe(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  Polygon argument;
  in >> argument;
  if (!in)
  {
    throw std::invalid_argument("Wrong argument");
  }
  Polygon frameRectangle = getBoundingBox(value);
  if (argument <= frameRectangle)
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

void marfina::echo(std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("Wrong argument");
  }
  size_t duplicateCount = std::count(value.begin(), value.end(), polygon);
  std::vector< Polygon > tempValue(value.size() + duplicateCount);
  size_t polygonCount = 0;
  for (const auto& shape: value)
  {
    tempValue.push_back(shape);
    if (shape == polygon)
    {
      ++polygonCount;
      tempValue.push_back(polygon);
    }
  }
  value = tempValue;
  out << polygonCount;
}
