#include "commands.hpp"
#include <iomanip>
#include <cmath>
#include <algorithm>

namespace prokopenko
{
  void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& p) {
      return p.getPoints().size() % 2 != 0;
      });
    out << count << '\n';
  }

  void CountEven(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& p) {
      return p.getPoints().size() % 2 == 0;
      });
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), [n](const Polygon& p) {
      return p.getPoints().size() == n;
      });
    out << count << '\n';
  }

  void Area(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    double total = 0.0;
    for (const auto& p : polygons)
    {
      total += p.getArea();
    }
    out << std::fixed << std::setprecision(1) << total << '\n';
  }

  void AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    double total = 0.0;
    for (const auto& p : polygons)
    {
      if (p.getPoints().size() % 2 != 0)
      {
        total += p.getArea();
      }
    }
    out << std::fixed << std::setprecision(1) << total << '\n';
  }

  void AreaEven(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    double total = 0.0;
    for (const auto& p : polygons)
    {
      if (p.getPoints().size() % 2 == 0)
      {
        total += p.getArea();
      }
    }
    out << std::fixed << std::setprecision(1) << total << '\n';
  }

  void AreaN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n)
  {
    double total = 0.0;
    for (const auto& p : polygons)
    {
      if (p.getPoints().size() == n)
      {
        total += p.getArea();
      }
    }
    out << std::fixed << std::setprecision(1) << total << '\n';
  }

  void MaxArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    double maxArea = 0.0;
    for (const auto& p : polygons)
    {
      maxArea = std::max(maxArea, p.getArea());
    }
    out << std::fixed << std::setprecision(1) << maxArea << '\n';
  }

  void MinArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0.0\n";
      return;
    }
    double minArea = polygons[0].getArea();
    for (const auto& p : polygons)
    {
      minArea = std::min(minArea, p.getArea());
    }
    out << std::fixed << std::setprecision(1) << minArea << '\n';
  }

  void MaxVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t maxV = 0;
    for (const auto& p : polygons)
    {
      maxV = std::max(maxV, p.getPoints().size());
    }
    out << maxV << '\n';
  }

  void MinVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0\n";
      return;
    }
    size_t minV = polygons[0].getPoints().size();
    for (const auto& p : polygons)
    {
      minV = std::min(minV, p.getPoints().size());
    }
    out << minV << '\n';
  }

  void MeanArea(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0.0\n";
      return;
    }
    double total = 0.0;
    for (const auto& p : polygons)
    {
      total += p.getArea();
    }
    out << std::fixed << std::setprecision(1) << (total / polygons.size()) << '\n';
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i + 1 < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i] == polygons[j])
        {
          ++count;
        }
      }
    }
    out << count << '\n';
  }

  void Right(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& p) {
      return p.isRight();
      });
    out << count << '\n';
  }

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i + 1 < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].isPermOf(polygons[j]))
        {
          ++count;
        }
      }
    }
    out << count << '\n';
  }

  void Less(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i + 1 < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].getArea() < polygons[j].getArea())
        {
          ++count;
        }
      }
    }
    out << count << '\n';
  }

  void More(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i + 1 < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (polygons[i].getArea() > polygons[j].getArea())
        {
          ++count;
        }
      }
    }
    out << count << '\n';
  }

  void Equal(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i + 1 < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        if (std::abs(polygons[i].getArea() - polygons[j].getArea()) < 1e-6)
        {
          ++count;
        }
      }
    }
    out << count << '\n';
  }
}
