#include "COMBS.hpp"

namespace vlad {

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

void area(const std::vector<Polygon>& polygons, const std::string& sub_command) {
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
    }
    else if (sub_command == "ODD") {
        area = std::accumulate(polygons.begin(), polygons.end(), area,
            [](const double sum, const Polygon& p) {
                if (p.points.size() % 2 != 0) {
                    return sum + calculateArea(p);
                }
                return sum;
            });
        std::cout << std::fixed << std::setprecision(1) << area << std::endl;
    }
    else if (sub_command == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }
        area = std::accumulate(polygons.begin(), polygons.end(), area,
            [](const double sum, const Polygon& p) {
                return sum + calculateArea(p);
            });
        std::cout << std::fixed << std::setprecision(1) << area / static_cast<double>(polygons.size()) << std::endl;
    }
    else {
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
        }
        catch (const std::exception& e) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}

void max(const std::vector<Polygon>& polygons, const std::string& sub_command) {
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
    }
    else if (sub_command == "VERTEXES") {
        size_t max_number_of_vertices = std::accumulate(polygons.begin(), polygons.end(), 0,
            [](const size_t number_of_vertices, const Polygon& p) {
                if (p.points.size() > number_of_vertices) {
                    return p.points.size();
                }
                return number_of_vertices;
            });
        std::cout << max_number_of_vertices << std::endl;
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

void min(const std::vector<Polygon>& polygons, const std::string& sub_command) {
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
    }
    else if (sub_command == "VERTEXES") {
        size_t min_number_of_vertices = std::accumulate(polygons.begin(), polygons.end(), 255,
            [](const size_t number_of_vertices, const Polygon& p) {
                if (p.points.size() < number_of_vertices) {
                    return p.points.size();
                }
                return number_of_vertices;
            });
        std::cout << min_number_of_vertices << std::endl;
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

void count(const std::vector<Polygon>& polygons, const std::string& sub_command) {
    long long count = 0;
    if (sub_command == "EVEN") {
        count = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& p) {
            return p.points.size() % 2 == 0;
        });
        std::cout << count << std::endl;
    }
    else if (sub_command == "ODD") {
        count = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& p) {
            return p.points.size() % 2 != 0;
        });
        std::cout << count << std::endl;
    }
    else {
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
        }
        catch (const std::exception& e) {
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

void perms(const std::vector<Polygon>& polygons, std::stringstream& params) {
    std::string polygon_str;
    std::getline(params, polygon_str);
    if (!polygon_str.empty() and polygon_str[0] == ' ') {
        polygon_str.erase(0, 1);
    }

    try {
        Polygon polygon = parsePolygon(polygon_str);
        long long count = std::count_if(polygons.cbegin(), polygons.cend(), [&polygon](const Polygon& p) {
            return perms(p, polygon);
        });
        std::cout << count << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

static Polygon readPolygonFromStream(std::stringstream& ss) {
    int n;
    ss >> n;
    Polygon p;
    p.points.resize(n);
    for (int i = 0; i < n; ++i) {
        char ch1, ch2, ch3;
        int x, y;
        ss >> ch1 >> x >> ch2 >> y >> ch3;
        p.points[i] = {x, y};
    }
    return p;
}

void maxSeq(const std::vector<Polygon>& poly, std::stringstream& input) {
    Polygon target = readPolygonFromStream(input);
    int max_seq = 0, cur_seq = 0;
    for (const auto& p : poly) {
        if (p == target) {
            ++cur_seq;
            if (cur_seq > max_seq) max_seq = cur_seq;
        } else {
            cur_seq = 0;
        }
    }
    if(max_seq == 0) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    else{
        std::cout << max_seq << std::endl;
    }
}

}

