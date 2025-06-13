#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace prokopenko
{
  void CountEven(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 0; });
    out << count << '\n';
  }

  void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 1; });
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [n](const Polygon& p) { return p.points.size() == n; });
    out << count << '\n';
  }

  void Area(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (const auto& p : polygons)
    {
      out << p.getArea() << '\n';
    }
  }

  void AreaEven(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (const auto& p : polygons)
    {
      if (p.points.size() % 2 == 0)
        out << p.getArea() << '\n';
    }
  }

  void AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (const auto& p : polygons)
    {
      if (p.points.size() % 2 == 1)
        out << p.getArea() << '\n';
    }
  }

  void AreaN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n)
  {
    for (const auto& p : polygons)
    {
      if (p.points.size() == n)
        out << p.getArea() << '\n';
    }
  }

  void MeanArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0.0\n";
      return;
    }

    double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double sum, const Polygon& p) {
        return sum + p.getArea();
      });
    double mean = total / polygons.size();
    out << std::fixed << std::setprecision(1) << mean << '\n';
  }

  void MaxArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0.0\n";
      return;
    }

    double maxArea = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
      })->getArea();
    out << std::fixed << std::setprecision(1) << maxArea << '\n';
  }

  void MaxVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0\n";
      return;
    }

    size_t maxVerts = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      })->points.size();
    out << maxVerts << '\n';
  }

  void MinArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0.0\n";
      return;
    }

    double minArea = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
      })->getArea();
    out << std::fixed << std::setprecision(1) << minArea << '\n';
  }

  void MinVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0\n";
      return;
    }

    size_t minVerts = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      })->points.size();
    out << minVerts << '\n';
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i] == polygons[j])
          ++count;
      }
    }
    out << count << '\n';
  }

  void Right(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.isRight(); });
    out << count << '\n';
  }

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].isPermOf(polygons[j]))
          ++count;
      }
    }
    out << count << '\n';
  }

  void Less(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].getArea() < polygons[j].getArea())
          ++count;
      }
    }
    out << count << '\n';
  }

  void More(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].getArea() > polygons[j].getArea())
          ++count;
      }
    }
    out << count << '\n';
  }

  void Equal(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (std::abs(polygons[i].getArea() - polygons[j].getArea()) < 1e-6)
          ++count;
      }
    }
    out << count << '\n';
  }
}
