#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <functional>
#include <cmath>
#include <limits>
#include <stdexcept>
using namespace std::placeholders;

bool Polygon::hasRightAngle() const {
    auto dotProduct = [](const Point& a, const Point& b, const Point& c) {
        int abx = b.x - a.x;
        int aby = b.y - a.y;
        int bcx = c.x - b.x;
        int bcy = c.y - b.y;
        return abx * bcx + aby * bcy;
    };

    for (size_t i = 0; i < points.size(); ++i) {
        const Point& prev = points[(i + points.size() - 1) % points.size()];
        const Point& curr = points[i];
        const Point& next = points[(i + 1) % points.size()];
        if (dotProduct(prev, curr, next) == 0) {
            return true;
        }
    }
    return false;
}

bool isPolygonValid(const Polygon& poly) {
    if (poly.points.size() < 3) return false;
    for (size_t i = 0; i < poly.points.size(); ++i) {
        for (size_t j = i + 1; j < poly.points.size(); ++j) {
            if (poly.points[i] == poly.points[j]) {
                return false;
            }
        }
    }
    return true;
}

double calculateArea(const Polygon& polygon) {
    if (!isPolygonValid(polygon)) return 0.0;
    double area = 0.0;
    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += (polygon.points[i].x * polygon.points[j].y) -
                (polygon.points[j].x * polygon.points[i].y);
    }
    return std::abs(area) / 2.0;
}

double calculateArea(const std::vector<Polygon>& polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double sum, const Polygon& p) { return sum + calculateArea(p); });
}

// Чтение из файла
std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file");

    auto parsePoint = [](std::istringstream& iss, Point& p) -> bool {
        char discard;
        return (iss >> discard && discard == '(' &&
                iss >> p.x &&
                iss >> discard && discard == ';' &&
                iss >> p.y &&
                iss >> discard && discard == ')');
    };

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t vertexCount;
        if (iss >> vertexCount) {
            Polygon poly;
            Point p;
            bool valid = true;
            for (size_t i = 0; i < vertexCount && valid; ++i) {
                if (!parsePoint(iss, p)) {
                    valid = false;
                    break;
                }
                poly.points.push_back(p);
                if (i < vertexCount - 1 && !(iss >> std::ws) && iss.peek() != EOF) {
                    valid = false;
                }
            }
            if (valid && poly.points.size() == vertexCount && isPolygonValid(poly)) {
                polygons.push_back(poly);
            }
        }
    }
    return polygons;
}

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    if (arg == "EVEN") {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return sum + (p.points.size() % 2 == 0 ? calculateArea(p) : 0.0);
            });
        std::cout << sum << '\n';
    }
    else if (arg == "ODD") {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return sum + (p.points.size() % 2 != 0 ? calculateArea(p) : 0.0);
            });
        std::cout << sum << '\n';
    }
    else if (arg == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto sum = calculateArea(polygons);
        std::cout << sum / polygons.size() << '\n';
    }
    else {
        try {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("Invalid vertex count");
            auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double sum, const Polygon& p) {
                    return sum + (p.points.size() == num ? calculateArea(p) : 0.0);
                });
            std::cout << sum << '\n';
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*maxIt) << '\n';
    }
    else if (arg == "VERTEXES") {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << maxIt->points.size() << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void minCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*minIt) << '\n';
    }
    else if (arg == "VERTEXES") {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << minIt->points.size() << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void countCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    auto countIf = [&polygons](const std::function<bool(size_t)>& pred) {
        return std::count_if(polygons.begin(), polygons.end(),
            [&pred](const Polygon& p) { return pred(p.points.size()); });
    };

    if (arg == "EVEN") {
        std::cout << countIf([](size_t n) { return n % 2 == 0; }) << '\n';
    }
    else if (arg == "ODD") {
        std::cout << countIf([](size_t n) { return n % 2 != 0; }) << '\n';
    }
    else {
        try {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("Invalid vertex count");
            std::cout << countIf([num](size_t n) { return n == num; }) << '\n';
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void rightShapesCommand(const std::vector<Polygon>& polygons) {
    auto count = std::count_if(polygons.begin(), polygons.end(),
        std::bind(&Polygon::hasRightAngle, _1));
    std::cout << count << '\n';
}

bool isPointInFrame(const Point& p, const Polygon& frame) {
    auto [minX, maxX] = std::minmax_element(frame.points.begin(), frame.points.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(frame.points.begin(), frame.points.end(),
        [](const Point& a, const Point& b) { return a.y < b.y; });

    return p.x >= minX->x && p.x <= maxX->x && p.y >= minY->y && p.y <= maxY->y;
}

void inframeCommand(std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<FALSE>\n";
        return;
    }

    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream iss(pointStr);

        auto parsePoint = [](std::istringstream& iss, Point& p) -> bool {
            char discard;
            return (iss >> discard && discard == '(' &&
                    iss >> p.x &&
                    iss >> discard && discard == ';' &&
                    iss >> p.y &&
                    iss >> discard && discard == ')');
        };

        Point p;
        for (size_t i = 0; i < vertexCount; ++i) {
            if (!parsePoint(iss, p)) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
        }

        if (!isPolygonValid(poly)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        int minX = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int minY = std::numeric_limits<int>::max();
        int maxY = std::numeric_limits<int>::min();

        for (const auto& polygon : polygons) {
            for (const auto& point : polygon.points) {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }

        bool allInside = std::all_of(poly.points.begin(), poly.points.end(),
            [=](const Point& point) {
                return point.x >= minX && point.x <= maxX &&
                       point.y >= minY && point.y <= maxY;
            });

        std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void processCommands(std::vector<Polygon>& polygons) {
    std::string command;
    while (std::cin >> command) {
        try {
            if (command == "AREA") {
                std::string arg;
                std::cin >> arg;
                areaCommand(polygons, arg);
            }
            else if (command == "MAX") {
                std::string arg;
                std::cin >> arg;
                maxCommand(polygons, arg);
            }
            else if (command == "MIN") {
                std::string arg;
                std::cin >> arg;
                minCommand(polygons, arg);
            }
            else if (command == "COUNT") {
                std::string arg;
                std::cin >> arg;
                countCommand(polygons, arg);
            }
            else if (command == "INFRAME") {
                std::string arg;
                std::cin >> arg;
                inframeCommand(polygons, arg);
            }
            else if (command == "RIGHTSHAPES") {
                rightShapesCommand(polygons);
            }
            else {
                std::cout << "<INVALID COMMAND>\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        catch (const std::exception& e) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
