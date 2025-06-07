#include "geometry.hpp"

bool isRectangle(const Polygon& polygon)
{
    if (polygon.points.size() != 3)
        return false;
    return true;
}

void Rects(const std::vector<Polygon>& polygons)
{
    std::size_t count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    std::cout << count << "\n";
}