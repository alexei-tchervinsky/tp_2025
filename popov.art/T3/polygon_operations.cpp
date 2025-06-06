#include "polygon_operations.hpp"
#include "geometry.hpp"
#include "iofmtguard.hpp"

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <iomanip>
#include <vector>
#include <iterator>
namespace {
  bool isEven(const popov::Polygon& polygon) { return (polygon.points.size() % 2 == 0); }
  bool isOdd(const popov::Polygon& polygon) { return !(polygon.points.size() % 2 == 0); }
  bool isSize(const popov::Polygon& polygon, size_t numPoints) { return (polygon.points.size() == numPoints); }
  bool comparatorPoints(const popov::Polygon& lhs, const popov::Polygon& rhs) { return lhs.points.size() < rhs.points.size(); }
  bool comparatorArea(const popov::Polygon& lhs, const popov::Polygon& rhs) { return getPolygonArea(lhs) < getPolygonArea(rhs); }
}
void popov::rmecho(std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (!in || polygon.points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }

    auto it = std::remove(value.begin(), value.end(), polygon);
    size_t count = std::distance(it, value.end());
    value.erase(it, value.end());
    out << count;
}
void popov::intersections(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
    Polygon target;
    in >> target;
    if (!in || target.points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    size_t count = 0;
    Polygon targetBB = getBoundingBox({target});
    for (const auto& poly : value) {
        Polygon polyBB = getBoundingBox({poly});
        bool intersects = !(polyBB <= targetBB) && !(targetBB <= polyBB);
        if (intersects) {
            count++;
        }
    }
    out << count;
}
void popov::lessArea(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
    Polygon target;
    in >> target;
    if (!in || target.points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    double targetArea = getPolygonArea(target);
    size_t count = std::count_if(value.begin(), value.end(),
        [targetArea](const Polygon& poly) {
            return getPolygonArea(poly) < targetArea;
        });
    out << count;
}
void popov::area(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
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
void popov::max(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
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
void popov::min(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
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
void popov::count(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
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
void popov::rightshapes(const std::vector<Polygon>& value, std::ostream& out)
{
  using namespace std::placeholders;
  out << std::count_if(value.cbegin(), value.cend(), isRightAngle);
}
void popov::inframe(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
    Polygon target;
    in >> target;
    if (!in || target.points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    Polygon frame = getBoundingBox(value);
    bool isInside = true;
    for (const auto& p : target.points) {
        if (p.x < findMinX(frame) || p.x > findMaxX(frame) ||
            p.y < findMinY(frame) || p.y > findMaxY(frame)) {
            isInside = false;
            break;
        }
    }
    out << (isInside ? "<TRUE>" : "<FALSE>");
}
void popov::echo(std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (!in || polygon.points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    size_t count = 0;
    for (const auto& p : value) {
        if (p == polygon) {
            count++;
        }
    }
    for (size_t i = 0; i < count; ++i) {
        value.push_back(polygon);
    }
    out << count;
}
