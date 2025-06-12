#include "commands.hpp"
#include <cmath>
#include <algorithm>

namespace prokopenko
{
  double calculate_area(const Polygon& polygon)
  {
    double area = 0.0;
    size_t n = polygon.size();
    for (size_t i = 0; i < n; ++i)
    {
      const Point& p1 = polygon[i];
      const Point& p2 = polygon[(i + 1) % n];
      area += (p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(area) / 2.0;
  }

  double area_param(const std::vector<Polygon>& data, std::istream&, std::ostream& out)
  {
    double total = 0.0;
    for (const auto& poly : data)
    {
      total += calculate_area(poly);
    }
    out << total << '\n';
    return total;
  }

  double max_param(const std::vector<Polygon>& data, std::istream&, std::ostream& out)
  {
    if (data.empty())
    {
      out << "0\n";
      return 0.0;
    }
    double max_area = 0.0;
    for (const auto& poly : data)
    {
      max_area = std::max(max_area, calculate_area(poly));
    }
    out << max_area << '\n';
    return max_area;
  }

  double min_param(const std::vector<Polygon>& data, std::istream&, std::ostream& out)
  {
    if (data.empty())
    {
      out << "0\n";
      return 0.0;
    }
    double min_area = calculate_area(data.front());
    for (const auto& poly : data)
    {
      min_area = std::min(min_area, calculate_area(poly));
    }
    out << min_area << '\n';
    return min_area;
  }

  size_t count_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
  {
    size_t vertex_count = 0;
    in >> vertex_count;
    size_t count = std::count_if(data.begin(), data.end(), [vertex_count](const Polygon& poly) {
      return poly.size() == vertex_count;
      });
    out << count << '\n';
    return count;
  }

  std::vector<Polygon> rects_param(const std::vector<Polygon>& data, std::istream&, std::ostream& out)
  {
    std::vector<Polygon> rectangles;
    for (const auto& poly : data)
    {
      if (poly.size() == 4)
      {
        rectangles.push_back(poly);
      }
    }
    for (const auto& rect : rectangles)
    {
      out << rect << '\n';
    }
    return rectangles;
  }

  size_t maxseq_param(const std::vector<Polygon>& data, std::istream&, std::ostream& out)
  {
    if (data.empty())
    {
      out << "0\n";
      return 0;
    }

    size_t max_seq = 1;
    size_t curr_seq = 1;
    double last_area = calculate_area(data[0]);

    for (size_t i = 1; i < data.size(); ++i)
    {
      double area = calculate_area(data[i]);
      if (area > last_area)
      {
        ++curr_seq;
        max_seq = std::max(max_seq, curr_seq);
      }
      else
      {
        curr_seq = 1;
      }
      last_area = area;
    }

    out << max_seq << '\n';
    return max_seq;
  }
}
