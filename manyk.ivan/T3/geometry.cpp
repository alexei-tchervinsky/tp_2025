#include "geometry.hpp"

std::istream& operator>>(std::istream& in, Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Point temp = { 0, 0 };
    in >> DelimiterChar{ '(' } >> temp.x >> DelimiterChar{ ';' } >> temp.y >> DelimiterChar{ ')' };
    if (in)
    {
        point = temp;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::size_t countPoints = 0;
    in >> countPoints;
    if (countPoints < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector<Point> temp;
    std::copy_n(std::istream_iterator<Point>{ in }, countPoints , std::back_inserter(temp));
    if (in.peek() != '\n')
    {
        in.setstate(std::ios::failbit);
    }
    if (in && (temp.size() == countPoints))
    {
        polygon.points = std::move(temp);
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DelimiterChar&& exp)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << '(' << p.x << ';' << p.y << ')';
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    out << poly.points.size();
    for (const auto& p : poly.points) {
        out << ' ' << p;
    }
    return out;
}