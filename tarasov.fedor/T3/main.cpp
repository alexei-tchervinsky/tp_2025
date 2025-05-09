#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>

struct Point {
    int x,y;

    bool operator<(const Point &other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

struct Polygon {
    std::vector <Point> points{};
};

std::istream& operator>>(std::istream& in, Point& p) {
    const std::istream::sentry sentry(in);
    if (!sentry) return in;

    char dummy;
    in >> dummy >> p.x >> dummy >> p.y >> dummy;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    const std::ostream::sentry sentry(out);
    if (!sentry) return out;

    out << "(" << p.x << ";" << p.y << ")";
    return out;
}

Polygon parsePolygon(const std::string& str) {
    std::istringstream ss(str);
    Polygon p;
    size_t number_of_vertices;
    ss >> number_of_vertices;

    if (ss.fail() || number_of_vertices < 3) {
        throw std::runtime_error("Неправильный ввод");
    }
    p.points.resize(number_of_vertices);
    for (size_t i = 0; i < number_of_vertices; ++i) {
        if (!(ss >> p.points[i])) {
            throw std::runtime_error("Неверные координаты");
        }
    }

    std::string remaining;
    if (ss >> remaining && !remaining.empty()) {
        throw std::runtime_error("Большое количество точек");
    }
    return p;
}


std::vector<Polygon> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Нельзя открыть файл: " << fileName << std::endl;
        exit(1);
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || std::all_of(line.begin(), line.end(), [](unsigned char c){ return std::isspace(c);})) {
            continue;
        }

        try {
            Polygon p = parsePolygon(line);
            polygons.push_back(p);
        } catch (const std::runtime_error& e) {}
    }
    file.close();
    return polygons;
}

double calculateArea(const Polygon& polygon) {
    double area = 0.0;
    for (size_t i = 0; i < polygon.points.size(); ++i) {
        const Point& p1 = polygon.points[i];
        const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
        area += static_cast<double>(p1.x * p2.y) - static_cast<double>(p1.y * p2.x);

    }
    return std::abs(area) / 2.0;
}

void areaCommand(std::vector<Polygon>& polygons, const std::string& sub_command) {
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

void maxCommand(std::vector<Polygon>& polygons, const std::string& sub_command) {
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

void minCommand(std::vector<Polygon>& polygons, const std::string& sub_command) {
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Используйте: ./lab filename" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> polygons = readFile(filename);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);

        std::string command;
        ss >> command;

        if (command == "AREA") {
            std::string sub_command;
            ss >> sub_command;
            areaCommand(polygons, sub_command);
        } else if (command == "MAX") {
            std::string sub_command;
            ss >> sub_command;
            maxCommand(polygons, sub_command);
        } else if (command == "MIN") {
            std::string sub_command;
            ss >> sub_command;
            minCommand(polygons, sub_command);
        } else if (command == "COUNT") {
            std::string sub_command;
            ss >> sub_command;
            countCommand(polygons, sub_command);
        } else if (command == "PERMS") {
            permsCommand(polygons, ss);
        } else if (command == "RIGHTSHAPES") {
            rightShapesCommand(polygons);
        }
        else {
            bool empty_input = true;
            for (char c : line) {
                if (!std::isspace(static_cast<unsigned char>(c))) {
                    empty_input = false;
                    break;
                }
            }
            if (!empty_input && !command.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            } else if (empty_input && std::cin.eof()) {
                break;
            }
        }
        if (std::cin.eof()) {
            break;
        }
    }
    return 0;
}
