#include "DataStruct.hpp"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <limits>

namespace nspace
{
    bool Point::operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool Polygon::operator==(const Polygon &other) const
    {
        return points == other.points;
    }

    double Polygon::area() const
    {
        if (points.size() < 3) return 0.0;
        double sum = std::accumulate(
            points.begin(),
            points.end(),
            0.0,
            [this](double acc, const Point& p1)
            {
                const Point& p2 = points[(&p1 - &points[0] + 1) % points.size()];
                return acc + (p1.x * p2.y) - (p1.y * p2.x);
            }
        );
        return std::abs(sum) / 2;
    }

    std::istream& operator>>(std::istream& in, Point& point)
    {
        char ignore;
        if (!(in >> ignore)) return in;
        if (ignore != '(')
        {

            LOG(ignore)

            LOG("** ошибка со чтением точки ( **\n")
            in.putback(ignore);
            in.setstate(std::ios::failbit);
            throw std::logic_error(INV_CMD);
        }

        if (!(in >> point.x))
        {
            LOG("** ошибка со чтением точки x **\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!(in >> ignore)) return in;
        if (ignore != ';')
        {
            LOG("** ошибка со чтением точки ; **\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!(in >> point.y))
        {
            LOG("** ошибка со чтением точки y **\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!(in >> ignore)) return in;
        if (ignore != ')')
        {
            LOG("** ошибка со чтением точки )**\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, Polygon& poly)
    {
        size_t numPoints;
        if (!(in >> numPoints))
        {
            LOG("** количество точек невалидно **\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        if (numPoints < 3)
        {
            LOG("** точек < 3 **\n")
            in.setstate(std::ios::failbit);
            return in;
        }

        poly.points.clear();  // Очищаем старые точки

        // Временный вектор для точек
        std::vector<Point> temp_points;
        std::copy_n(std::istream_iterator<Point>(in), numPoints, std::back_inserter(temp_points));
        auto it_start = temp_points.begin();
        auto it_end = temp_points.end();
        if ((static_cast<size_t>(it_end - it_start)) != numPoints)
        {
            LOG("** copy_n copy LESS THAN expected **\n")
            in.setstate(std::ios::failbit);
            return in;
        }
        else
        {
            LOG("** copy_n copy EXACTLY AS expected **")
        }

        if (in.fail())
        {
            LOG("** ошибка std::copy_n **\n")
            std::cin.clear();
            return in;
        }

        std::string tail;
        std::getline(in, tail);
        LOG(tail.size())
        LOG(tail.c_str())
        if (tail.size() > 1)
        {
            in.setstate(std::ios::failbit);
            // std::cout << in.get();
            // in.putback('X');
            // in.putback('\n');
            LOG("** ошибка, лишние точки: ") LOG(tail) LOG(" **\n")
            return in;
        }

        if (temp_points.size() != numPoints)
        {
            in.setstate(std::ios::failbit);
            LOG("** ошибка, неверное количество точек **\n")
            return in;
        }

        // Проверка на дубликаты
        if (std::adjacent_find(temp_points.begin(), temp_points.end()) != temp_points.end())
        {
            LOG("** ошибка, дубликаты точек **\n")
            temp_points.clear();
            in.setstate(std::ios::failbit);
            return in;
        }

        // Если все в порядке, присваиваем точки полигону
        poly.points = std::move(temp_points);

        LOG("** Полигон: ") LOG(poly) LOG(" **\n")
        in.clear();
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        return out << "(" << point.x << "," << point.y << ")";
    }

    std::ostream& operator<<(std::ostream& out, const Polygon& poly)
    {
        out << poly.points.size() << " ";
        std::copy(poly.points.begin(), poly.points.end(),
                  std::ostream_iterator<Point>(out, " "));
        return out;
    }

    bool AreaComparator::operator()(const Polygon& a, const Polygon& b) const
    {
        return a.area() < b.area();
    }

    bool VertexCountComparator::operator()(const Polygon& a, const Polygon& b) const
    {
        return a.points.size() < b.points.size();
    }
}
