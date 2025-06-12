#include "commands.hpp"
#include <map>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>
#include <set>

void prokopenko::outMessage(std::ostream& out, const std::string& message)
{
  out << message;
}

// ===== AREA =====

void prokopenko::Area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> areas;
  areas["EVEN"] = AreaEven;
  areas["ODD"] = AreaOdd;
  areas["MEAN"] = AreaMean;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");

  std::string parameter;
  in >> parameter;
  try {
    areas.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range&) {
    if (std::all_of(parameter.begin(), parameter.end(), ::isdigit) && std::stoi(parameter) > 2) {
      AreaVersNum(std::stoi(parameter), polygons, out);
    }
    else {
      outInvalid(out);
    }
  }
}

void prokopenko::AreaEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> even;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even),
    [](const Polygon& p) { return p.points.size() % 2 == 0; });
  double sum = sumAreas(even);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void prokopenko::AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> odd;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd),
    [](const Polygon& p) { return p.points.size() % 2 == 1; });
  double sum = sumAreas(odd);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void prokopenko::AreaMean(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty()) throw std::out_of_range("");
  double sum = sumAreas(polygons);
  out << std::setprecision(1) << std::fixed << sum / polygons.size() << '\n';
}

void prokopenko::AreaVersNum(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> filtered;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtered),
    [vertexes](const Polygon& p) { return p.points.size() == vertexes; });
  double sum = sumAreas(filtered);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

double prokopenko::sumAreas(const std::vector<Polygon>& polygons)
{
  std::vector<double> areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas),
    [](const Polygon& p) { return getArea(p); });
  return std::accumulate(areas.begin(), areas.end(), 0.0);
}

double prokopenko::getArea(const Polygon& polygon)
{
  double sum = 0.0, diff = 0.0;
  for (size_t i = 0; i < polygon.points.size(); ++i) {
    const Point& a = polygon.points[i];
    const Point& b = polygon.points[(i + 1) % polygon.points.size()];
    sum += a.x * b.y;
    diff += a.y * b.x;
  }
  return 0.5 * std::abs(sum - diff);
}

// ===== MAX =====

void prokopenko::Max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> maxes;
  maxes["AREA"] = maxArea;
  maxes["VERTEXES"] = maxVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");

  std::string parameter;
  in >> parameter;
  try {
    maxes.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range&) {
    outInvalid(out);
  }
}

void prokopenko::maxArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty()) throw std::out_of_range("");
  auto maxIt = std::max_element(polygons.begin(), polygons.end(),
    [](const Polygon& a, const Polygon& b) {
      return getArea(a) < getArea(b);
    });
  out << std::setprecision(1) << std::fixed << getArea(*maxIt) << '\n';
}

void prokopenko::maxVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty()) throw std::out_of_range("");
  std::vector<std::size_t> vertexes;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes),
    [](const Polygon& p) { return p.points.size(); });
  out << *std::max_element(vertexes.begin(), vertexes.end()) << '\n';
}

// ===== MIN =====

void prokopenko::Min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> mins;
  mins["AREA"] = minArea;
  mins["VERTEXES"] = minVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");

  std::string parameter;
  in >> parameter;
  try {
    mins.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range&) {
    outInvalid(out);
  }
}

void prokopenko::minArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty()) throw std::out_of_range("");
  std::vector<double> areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas),
    [](const Polygon& p) { return getArea(p); });
  out << std::setprecision(1) << std::fixed << *std::min_element(areas.begin(), areas.end()) << '\n';
}

void prokopenko::minVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty()) throw std::out_of_range("");
  std::vector<std::size_t> vertexes;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes),
    [](const Polygon& p) { return p.points.size(); });
  out << *std::min_element(vertexes.begin(), vertexes.end()) << '\n';
}

// ===== COUNT =====

void prokopenko::Count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::string param;
  in >> param;

  if (param == "EVEN") {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 0; });
    out << count << '\n';
  }
  else if (param == "ODD") {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 1; });
    out << count << '\n';
  }
  else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
    int n = std::stoi(param);
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
    }
    else {
      std::size_t count = std::count_if(polygons.begin(), polygons.end(),
        [n](const Polygon& p) { return static_cast<int>(p.points.size()) == n; });
      out << count << '\n';
    }
  }
  else {
    out << "<INVALID COMMAND>\n";
  }
}

// ===== PERMS =====

bool prokopenko::equalArea(const Polygon& a, const Polygon& b)
{
  return std::fabs(getArea(a) - getArea(b)) < 1e-6;
}

void prokopenko::Perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream&)
{
  for (const auto& polygon : polygons)
  {
    std::vector<Point> points = polygon.points;
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
      return std::tie(a.x, a.y) < std::tie(b.x, b.y);
      });

    std::set<std::vector<Point>> uniquePerms;
    do {
      Polygon permuted{ points };
      if (equalArea(permuted, polygon)) {
        uniquePerms.insert(points);
      }
    } while (std::next_permutation(points.begin(), points.end(), [](const Point& a, const Point& b) {
      return std::tie(a.x, a.y) < std::tie(b.x, b.y);
      }));

    out << uniquePerms.size() << '\n';
  }
}

// ===== RIGHTSHAPES =====

bool isRightAngle(const Point& a, const Point& b, const Point& c)
{
  int dx1 = b.x - a.x, dy1 = b.y - a.y;
  int dx2 = c.x - b.x, dy2 = c.y - b.y;
  return dx1 * dx2 + dy1 * dy2 == 0;
}

bool isRectangle(const Polygon& polygon)
{
  if (polygon.points.size() != 4) return false;
  const auto& p = polygon.points;

  return isRightAngle(p[0], p[1], p[2]) &&
    isRightAngle(p[1], p[2], p[3]) &&
    isRightAngle(p[2], p[3], p[0]) &&
    isRightAngle(p[3], p[0], p[1]);
}

void prokopenko::Rightshapes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  int count = 0;
  for (const auto& p : polygons)
  {
    if (isRectangle(p)) count++;
  }
  out << count << '\n';
}
