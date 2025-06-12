#include <cmath>
#include <algorithm>
#include <iterator>

#include "datastruct.hpp"
#include "ioObjects.hpp"

namespace orlov
{
    bool Point::operator==(const Point& other) const
    {
        return x_ == other.x_ && y_ == other.y_;
    }

    std::istream& operator>>(std::istream& is, Point& src)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        Point temp;

        is >> checkSymbol { '(' };
        is >> temp.x_ >> checkSymbol{ ';' } >> temp.y_;
        is >> checkSymbol{ ')' };

        if (is)
            src = temp;

        return is;
    }

    double Polygon::getArea() const
    {
        if (points.size() < 3) return 0.0;

        double area = 0.0;

        for(std::size_t i = 0; i < points.size(); ++i)
        {
            std::size_t j = (i + 1) % points.size();
            area += points[i].x_ * points[j].y_ - points[j].x_ * points[i].y_;
        }

        return std::abs(area) / 2.0;
    }

    bool Polygon::isInsideFrame(const Point leftBottom, const Point rightTop) const
    {
        return std::all_of(points.begin(), points.end(), [&](const Point& p)
        {
            return
                p.x_ >= leftBottom.x_ &&
                p.x_ <= rightTop.x_ &&
                p.y_ >= leftBottom.y_ &&
                p.y_ <= rightTop.y_
                ;
        });
    }

    bool Polygon::operator==(const Polygon& other) const
    {
        return points == other.points;
    }

    std::istream& operator>>(std::istream& is, Polygon& src)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::size_t count = 0;
        is >> count;

        std::string line;
        std::getline(is, line);
        std::istringstream iss(line);

        Polygon temp;

        std::copy(
            std::istream_iterator<Point>(iss),
            std::istream_iterator<Point>(),
            std::back_inserter(temp.points)
        );

        if (count < 3 || temp.points.size() != count)
        {
            is.setstate(std::ios::failbit);

            return is;
        }

        if (is)
            src = temp;

        return is;
    }
}

