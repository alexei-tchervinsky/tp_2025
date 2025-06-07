#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>

std::istream& geom_lab::operator>>(std::istream& in, DelimiterChar&& exp)
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

std::istream& geom_lab::operator>>(std::istream& in, DelimiterString&& exp)
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

std::istream& geom_lab::operator>>(std::istream& in, Point& point)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    using delChar = DelimiterChar;
    Point temp = { 0, 0 };
    in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >>
    delChar{ ')' };
    if (in)
    {
        point = temp;
    }
    return in;
}

bool geom_lab::operator==(const Point& lhs, const Point& rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool geom_lab::operator==(const Polygon& lhs, const Polygon& rhs)
{
    if (lhs.points.size() != rhs.points.size())
    {
        return false;
    }
    return std::equal(lhs.points.cbegin(), lhs.points.cend(),
                      rhs.points.cbegin());
}

bool geom_lab::operator<=(const Polygon& lhs, const Polygon& rhs)
{
    int innerMinX = findMinX(lhs);
    int innerMinY = findMinY(lhs);
    int innerMaxX = findMaxX(lhs);
    int innerMaxY = findMaxY(lhs);
    int outerMinX = findMinX(rhs);
    int outerMinY = findMinY(rhs);
    int outerMaxX = findMaxX(rhs);
    int outerMaxY = findMaxY(rhs);
    return (innerMinX >= outerMinX) && (innerMaxX <= outerMaxX) &&
    (innerMinY >= outerMinY) && (innerMaxY <= outerMaxY);
}

std::istream& geom_lab::operator>>(std::istream& in, Polygon& polygon)
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
    temp.reserve(countPoints);

    // Читаем точки по одной, проверяя каждую
    for (size_t i = 0; i < countPoints; ++i)
    {
        Point p;
        in >> p;
        if (!in)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        temp.push_back(p);
    }

    if (in && (temp.size() == countPoints))
    {
        polygon.points = temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

double geom_lab::AreaPolygon::operator()(double area, const Point& p2,
                                         const Point& p3)
{
    area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x)
                           * (p2.y - p1.y));
    p1 = p2;
    return area;
}

double geom_lab::getPolygonArea(const Polygon& polygon)
{
    if (polygon.points.size() < 3)
    {
        return 0.0;
    }

    // Shoelace formula
    double area = 0.0;
    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area += polygon.points[i].x * polygon.points[j].y;
        area -= polygon.points[j].x * polygon.points[i].y;
    }
    return std::abs(area) / 2.0;
}

bool geom_lab::isRightAngle(const Polygon& polygon)
{
    if (polygon.points.size() < 3)
    {
        return false;
    }

    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i)
    {
        Point p1 = polygon.points[i];
        Point p2 = polygon.points[(i + 1) % n];
        Point p3 = polygon.points[(i + 2) % n];

        Point vec1{ p2.x - p1.x, p2.y - p1.y };
        Point vec2{ p2.x - p3.x, p2.y - p3.y };

        if ((vec1.x * vec2.x + vec1.y * vec2.y) == 0)
        {
            return true;
        }
    }
    return false;
}

bool geom_lab::accumulateRightAngle::operator()(const Point& p3)
{
    Point vec1{ p2.x - p1.x, p2.y - p1.y };
    Point vec2{ p2.x - p3.x, p2.y - p3.y };
    p1 = p2;
    p2 = p3;
    return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}

namespace {
bool compareByX(const geom_lab::Point& lhs, const geom_lab::Point& rhs)
{ return lhs.x < rhs.x; }
bool compareByY(const geom_lab::Point& lhs, const geom_lab::Point& rhs)
{ return lhs.y < rhs.y; }
bool comparePolygonsByMaxX(const geom_lab::Polygon& lhs,
                           const geom_lab::Polygon& rhs)
{ return geom_lab::findMaxX(lhs)
    < geom_lab::findMaxX(rhs); }
bool comparePolygonsByMaxY(const geom_lab::Polygon& lhs,
                           const geom_lab::Polygon& rhs)
{ return geom_lab::findMaxY(lhs)
    < geom_lab::findMaxY(rhs); }
bool comparePolygonsByMinX(const geom_lab::Polygon& lhs,
                           const geom_lab::Polygon& rhs)
{ return geom_lab::findMinX(lhs) < geom_lab::findMinX(rhs); }
bool comparePolygonsByMinY(const geom_lab::Polygon& lhs,
                           const geom_lab::Polygon& rhs)
{ return geom_lab::findMinY(lhs) < geom_lab::findMinY(rhs); }
}

int geom_lab::findMaxX(const Polygon& polygon)
{
    return std::max_element(polygon.points.cbegin(),
                            polygon.points.cend(), compareByX)->x;
}

int geom_lab::findMaxY(const Polygon& polygon)
{
    return std::max_element(polygon.points.cbegin(),
                            polygon.points.cend(), compareByY)->y;
}

int geom_lab::findMinX(const Polygon& polygon)
{
    return std::min_element(polygon.points.cbegin(), polygon.points.cend(),
                            compareByX)->x;
}

int geom_lab::findMinY(const Polygon& polygon)
{
    return std::min_element(polygon.points.cbegin(), polygon.points.cend(),
                            compareByY)->y;
}

geom_lab::Polygon geom_lab::getBoundingBox(const std::vector<Polygon>& polygon)
{
    int pointMaxX = findMaxX(*std::max_element(polygon.cbegin(),
                                    polygon.cend(), comparePolygonsByMaxX));
    int pointMaxY = findMaxY(*std::max_element(polygon.cbegin(),
                                    polygon.cend(), comparePolygonsByMaxY));
    int pointMinX = findMinX(*std::min_element(polygon.cbegin(),
                                    polygon.cend(), comparePolygonsByMinX));
    int pointMinY = findMinY(*std::min_element(polygon.cbegin(),
                                    polygon.cend(), comparePolygonsByMinY));
    std::vector< Point > res{ {pointMinX, pointMinY},
        {pointMinX, pointMaxY}, {pointMaxX, pointMaxY},
        {pointMaxX, pointMinY} };
    return Polygon{ res };
}

namespace {
bool isEven(const geom_lab::Polygon& polygon)
{ return (polygon.points.size() % 2 == 0); }
bool isOdd(const geom_lab::Polygon& polygon)
{ return !(polygon.points.size() % 2 == 0); }
bool isSize(const geom_lab::Polygon& polygon, size_t numPoints)
{ return (polygon.points.size() == numPoints); }
bool comparatorPoints(const geom_lab::Polygon& lhs,
                      const geom_lab::Polygon& rhs)
{ return lhs.points.size() < rhs.points.size(); }
bool comparatorArea(const geom_lab::Polygon& lhs,
                    const geom_lab::Polygon& rhs)
{ return geom_lab::getPolygonArea(lhs) < geom_lab::getPolygonArea(rhs); }
}

void geom_lab::area(const std::vector<Polygon>& value,
                    std::istream& in, std::ostream& out)
{
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed;
    std::string argument = "";
    in >> argument;
    std::vector< Polygon > polygons;
    using namespace std::placeholders;
    if (argument == "EVEN")
    {
        std::copy_if(value.cbegin(), value.cend(),
                     std::back_inserter(polygons), isEven);
    }
    else if (argument == "ODD")
    {
        std::copy_if(value.cbegin(), value.cend(),
                     std::back_inserter(polygons), isOdd);
    }
    else if (argument == "MEAN")
    {
        if (value.empty())
        {
            throw std::logic_error("No polygons");
        }
        polygons = value;
    }
    else
    {
        size_t countPoints = std::stoull(argument);
        if (countPoints < 3)
        {
            throw std::logic_error("Wrong number");
        }
        std::function< bool(const Polygon&)
        > isCorrectCount = std::bind(isSize, _1, countPoints);
        std::copy_if(value.cbegin(), value.cend(),
                     std::back_inserter(polygons), isCorrectCount);
    }
    std::vector< double > areas;
    std::transform(polygons.cbegin(), polygons.cend(),
                   std::back_inserter(areas), getPolygonArea);
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    if (argument == "MEAN")
    {
        out << res / value.size();
    }
    else
    {
        out << res;
    }
}

void geom_lab::max(const std::vector<Polygon>& value, std::istream& in,
                   std::ostream& out)
{
    std::string argument = "";
    in >> argument;
    if (value.empty())
    {
        throw std::logic_error("No polygons");
    }
    if (argument == "AREA")
    {
        iofmtguard guard(out);
        out << std::setprecision(1) << std::fixed;
        out << getPolygonArea(*std::max_element(value.begin(),
                                                value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
        out << std::max_element(value.begin(), value.end(),
                                comparatorPoints)->points.size();
    }
    else
    {
        throw std::logic_error("Wrong argument");
    }
}

void geom_lab::min(const std::vector<Polygon>& value,
                   std::istream& in, std::ostream& out)
{
    std::string argument = "";
    in >> argument;
    if (value.empty())
    {
        throw std::logic_error("No polygons");
    }
    if (argument == "AREA")
    {
        iofmtguard guard(out);
        out << std::setprecision(1) << std::fixed;
        out << getPolygonArea(*std::min_element(value.begin(),
                                                value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
        out << std::min_element(value.begin(), value.end(),
                                comparatorPoints)->points.size();
    }
    else
    {
        throw std::logic_error("Wrong argument");
    }
}

void geom_lab::count(const std::vector<Polygon>& value,
                     std::istream& in, std::ostream& out)
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
        std::function< bool(const Polygon&) >
        isCorrectCount = std::bind(isSize, _1, countPoints);
        out << std::count_if(value.begin(), value.end(), isCorrectCount);
    }
}

void geom_lab::rightshapes(const std::vector<Polygon>& value, std::ostream& out)
{
    out << std::count_if(value.cbegin(), value.cend(), isRightAngle);
}

void geom_lab::inframe(const std::vector<Polygon>& value, std::istream& in,
                       std::ostream& out)
{
    Polygon argument;
    in >> argument;
    if (!in)
    {
        throw std::invalid_argument("Wrong argument");
    }
    if (value.empty())
    {
        throw std::logic_error("No polygons");
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

void geom_lab::echo(std::vector<Polygon>& value, std::istream& in,
                    std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
        throw std::logic_error("Wrong argument");
    }
    size_t polygonCount = 0;
    std::vector< Polygon > tempValue;
    tempValue.reserve(value.size() * 2);

    for (const auto& shape : value)
    {
        tempValue.push_back(shape);
        if (shape == polygon)
        {
            ++polygonCount;
            tempValue.push_back(polygon);
        }
    }
    value = std::move(tempValue);
    out << polygonCount;
}

// Variant 2 commands implementation

void geom_lab::lessarea(const std::vector<Polygon>& value,
                        std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
        throw std::logic_error("Wrong argument");
    }

    double targetArea = getPolygonArea(polygon);
    auto hasLessArea = [targetArea](const Polygon& p) {
        return getPolygonArea(p) < targetArea;
    };

    out << std::count_if(value.cbegin(), value.cend(), hasLessArea);
}

void geom_lab::maxseq(const std::vector<Polygon>& value,
                      std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
        throw std::logic_error("Wrong argument");
    }

    if (value.empty())
    {
        out << 0;
        return;
    }

    size_t maxSequence = 0;
    size_t currentSequence = 0;

    for (const auto& shape : value)
    {
        if (shape == polygon)
        {
            ++currentSequence;
            maxSequence = std::max(maxSequence, currentSequence);
        }
        else
        {
            currentSequence = 0;
        }
    }

    out << maxSequence;
}
