#include "commands.hpp"
#include <algorithm>
#include <unordered_set>

namespace prokopenko {

  namespace {
    using Filter = std::function<bool(const Polygon&)>;
    void printFiltered(const std::vector<Polygon>& polygons, std::ostream& out, Filter filter) {
      std::unordered_set<size_t> printed;
      for (size_t i = 0; i < polygons.size(); ++i) {
        if (!filter(polygons[i])) continue;
        bool alreadyPrinted = false;
        for (auto j : printed) {
          if (polygons[i].isPermOf(polygons[j])) {
            alreadyPrinted = true;
            break;
          }
        }
        if (!alreadyPrinted) {
          out << polygons[i] << '\n';
          printed.insert(i);
        }
      }
    }
  }

  void AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out) {
    printFiltered(polygons, out, [](const Polygon& p) {
      return p.points.size() % 2 != 0;
      });
  }

  void AreaEven(const std::vector<Polygon>& polygons, std::ostream& out) {
    printFiltered(polygons, out, [](const Polygon& p) {
      return p.points.size() % 2 == 0;
      });
  }

  void AreaN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n) {
    printFiltered(polygons, out, [n](const Polygon& p) {
      return p.points.size() == n;
      });
  }

  void MaxVertexes(const std::vector<Polygon>& polygons, std::ostream& out) {
    size_t maxV = 0;
    for (const auto& p : polygons)
      maxV = std::max(maxV, p.points.size());

    printFiltered(polygons, out, [maxV](const Polygon& p) {
      return p.points.size() == maxV;
      });
  }

  void MinVertexes(const std::vector<Polygon>& polygons, std::ostream& out) {
    if (polygons.empty()) return;
    size_t minV = polygons[0].points.size();
    for (const auto& p : polygons)
      minV = std::min(minV, p.points.size());

    printFiltered(polygons, out, [minV](const Polygon& p) {
      return p.points.size() == minV;
      });
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::vector<bool> printed(polygons.size(), false);
    for (size_t i = 0; i < polygons.size(); ++i) {
      if (printed[i]) continue;
      bool found = false;
      for (size_t j = i + 1; j < polygons.size(); ++j) {
        if (polygons[i] == polygons[j]) {
          if (!found) {
            out << polygons[i] << '\n';
            printed[i] = true;
            found = true;
          }
          printed[j] = true;
        }
      }
    }
  }

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::vector<bool> printed(polygons.size(), false);
    for (size_t i = 0; i < polygons.size(); ++i) {
      if (printed[i]) continue;
      bool found = false;
      for (size_t j = i + 1; j < polygons.size(); ++j) {
        if (polygons[i].isPermOf(polygons[j])) {
          if (!found) {
            out << polygons[i] << '\n';
            printed[i] = true;
            found = true;
          }
          printed[j] = true;
        }
      }
    }
  }

  void Equal(const std::vector<Polygon>& polygons, std::ostream& out) {
    std::vector<bool> printed(polygons.size(), false);
    for (size_t i = 0; i < polygons.size(); ++i) {
      if (printed[i]) continue;
      bool found = false;
      for (size_t j = i + 1; j < polygons.size(); ++j) {
        if (std::abs(polygons[i].getArea() - polygons[j].getArea()) < 1e-6) {
          if (!found) {
            out << polygons[i] << '\n';
            printed[i] = true;
            found = true;
          }
          printed[j] = true;
        }
      }
    }
  }

} // namespace prokopenko
