#include "command.hpp"

namespace tarasov {

double calculateArea(const Polygon& polygon) {
    double area = std::accumulate(polygon.points.begin(),
        std::prev(polygon.points.end()), 0.0,
        [&](double sum, const Point& p1) {
            const Point& p2 = *std::next(&p1);
            return sum + (p1.x * p2.y - p1.y * p2.x);
        });

    const Point& last_point = polygon.points.back();
    const Point& first_point = polygon.points.front();
    area += last_point.x * first_point.y - last_point.y * first_point.x;

    return std::abs(area) / 2.0;
}

void areaCommand(const std::vector<Polygon>& polygons, const std::string& sub_command) {
    double area = 0.0;
    if (sub_command == "EVEN") {
        area = std::accumulate(polygons.begin(), polygons.end(), area,
            [](const double sum, const Polygon& p) {
                if (p.points.size() % 2 == 0) {
                    return sum + calculateArea(p);
                }
                return sum;
            });
        std::cout << std::fixed << std::setprecision(1) << area << std::endl;
    } else if (sub_command == "ODD") {
        area = std::accumulate(polygons.begin(), polygons.end(), area,
            [](const double sum, const Polygon& p) {
                if (p.points.size() % 2 != 0) {
                    return sum + calculateArea(p);
                }
                return sum;
            });
        std::cout << std::fixed << std::setprecision(1) << area << std::endl;
    } else if (sub_command == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        area = std::accumulate(polygons.begin(), polygons.end(), area,
            [](const double sum, const Polygon& p) {
                return sum + calculateArea(p);
            });
        std::cout << std::fixed << std::setprecision(1) << area / static_cast<double>(polygons.size()) << std::endl;
    } else {
        try {
            size_t number_of_vertices = std::stol(sub_command);
            if (number_of_vertices < 3) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            area = std::accumulate(polygons.begin(), polygons.end(), area,
            [&number_of_vertices](const double sum, const Polygon& p) {
                if (p.points.size() == number_of_vertices) {
                    return sum + calculateArea(p);
                }
                return sum;
            });
            std::cout << std::fixed << std::setprecision(1) << area << std::endl;
        } catch (const std::exception& e) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}

void maxCommand(const std::vector<Polygon>& polygons, const std::string& sub_command) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    if (sub_command == "AREA") {
        double max_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](const double area, const Polygon& p) {
                if (calculateArea(p) > area) {
                    return calculateArea(p);
                }
                return area;
            });
        std::cout << std::fixed << std::setprecision(1) << max_area << std::endl;
    } else if (sub_command == "VERTEXES") {
        size_t max_number_of_vertices = std::accumulate(polygons.begin(), polygons.end(), 0,
            [](const size_t number_of_vertices, const Polygon& p) {
                if (p.points.size() > number_of_vertices) {
                    return p.points.size();
                }
                return number_of_vertices;
            });
        std::cout << max_number_of_vertices << std::endl;
    } else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

void minCommand(const std::vector<Polygon>& polygons, const std::string& sub_command) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    if (sub_command == "AREA") {
        double min_area = std::accumulate(polygons.begin(), polygons.end(), 1000.0,
            [](const double area, const Polygon& p) {
                if (calculateArea(p) < area) {
                    return calculateArea(p);
                }
                return area;
            });
        std::cout << std::fixed << std::setprecision(1) << min_area << std::endl;
    } else if (sub_command == "VERTEXES") {
        size_t min_number_of_vertices = std::accumulate(polygons.begin(), polygons.end(), 255,
            [](const size_t number_of_vertices, const Polygon& p) {
                if (p.points.size() < number_of_vertices) {
                    return p.points.size();
                }
                return number_of_vertices;
            });
        std::cout << min_number_of_vertices << std::endl;
    } else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

void countCommand(const std::vector<Polygon>& polygons, const std::string& sub_command) {
    long long count = 0;
    if (sub_command == "EVEN") {
        count = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& p) {
            return p.points.size() % 2 == 0;
        });
        std::cout << count << std::endl;
    } else if (sub_command == "ODD") {
        count = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& p) {
            return p.points.size() % 2 != 0;
        });
        std::cout << count << std::endl;
    } else {
        try {
            size_t number_of_vertices = std::stol(sub_command);
            if (number_of_vertices < 3) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            count = std::count_if(polygons.cbegin(), polygons.cend(), [&number_of_vertices](const Polygon& p) {
                return number_of_vertices == p.points.size();
            });
            std::cout << count << std::endl;
        } catch (const std::exception& e) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}

bool perms(Polygon p1, Polygon p2) {
    if (p1.points.size() != p2.points.size()) {
        return false;
    }

    std::sort(p1.points.begin(), p1.points.end());
    std::sort(p2.points.begin(), p2.points.end());
    return p1.points == p2.points;
}

void permsCommand(const std::vector<Polygon>& polygons, std::stringstream& params) {
    std::string polygon_str;

    std::getline(params, polygon_str);
    if (!polygon_str.empty() && polygon_str[0] == ' ') {
        polygon_str.erase(0, 1);
    }

    try {
        Polygon polygon = parsePolygon(polygon_str);
        long long count = std::count_if(polygons.cbegin(), polygons.cend(), [&polygon](const Polygon& p) {
            return perms(p, polygon);
        });
        std::cout << count << std::endl;
    } catch (const std::exception& e) {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

bool isRightAngle(Point a, Point b, Point c) {
    long long ba_x = static_cast<long long>(a.x) - b.x;
    long long ba_y = static_cast<long long>(a.y) - b.y;
    long long bc_x = static_cast<long long>(c.x) - b.x;
    long long bc_y = static_cast<long long>(c.y) - b.y;

    return (ba_x * bc_x + ba_y * bc_y) == 0;
}

bool hasRightAngle(const Polygon& polygon) {
    std::vector<Point> extended_polygon = polygon.points;
    extended_polygon.push_back(polygon.points.begin()[0]);
    extended_polygon.push_back(polygon.points.begin()[1]);

    size_t n = polygon.points.size();
    std::vector<size_t> indices(n);
    std::iota(indices.begin(), indices.end(), 0);


    bool result = std::any_of(indices.begin(), indices.end(),
                              [&extended_polygon](size_t i) {
                                  return isRightAngle(extended_polygon[i], extended_polygon[i + 1], extended_polygon[i + 2]);
                              });

    return result;
}

void rightShapesCommand(const std::vector<Polygon>& polygons) {
    long long count = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& p) {
        return hasRightAngle(p);
    });

    std::cout << count << std::endl;
}
}