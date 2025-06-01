#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <limits>
#include <vector>
#include <cmath>
#include <iomanip>
#include "geometry.hpp"
#include "iofmtguard.hpp"

namespace ilyaerofick {

struct DelimiterChar {
    char expected;
};

struct DelimiterString {
    const char* expected;
};

struct Point {
    int x;
    int y;
};

struct Polygon {
    std::vector<Point> points;
};

class IOFmtGuard {
public:
    explicit IOFmtGuard(std::basic_ios<char>& s);
    ~IOFmtGuard();
private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
};

} // namespace ilyaerofick

// Реализации операторов и функций
namespace ilyaerofick {

std::istream& operator>>(std::istream& in, DelimiterChar&& exp) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c = 0;
    in >> c;
    if (std::tolower(c) != exp.expected) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DelimiterString&& exp) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    size_t i = 0;
    while (exp.expected[i] != '\0') {
        in >> DelimiterChar{exp.expected[i]};
        ++i;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    Point temp{0, 0};
    in >> DelimiterChar{'('} >> temp.x >> DelimiterChar{';'}
       >> temp.y >> DelimiterChar{')'};
    if (in) point = temp;
    return in;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    size_t count = 0;
    in >> count;
    if (count < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector<Point> temp;
    using InputIt = std::istream_iterator<Point>;
    std::copy_n(InputIt{in}, count, std::back_inserter(temp));
    if (in && temp.size() == count) {
        polygon.points = temp;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

bool operator==(const Polygon& lhs, const Polygon& rhs) {
    if (lhs.points.size() != rhs.points.size()) return false;
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
}

double getArea(const Polygon& polygon) {
    double area = 0.0;
    for (size_t i = 0; i < polygon.points.size(); ++i) {
        const Point& p1 = polygon.points[i];
        const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
        area += (p1.x * p2.y) - (p2.x * p1.y);
    }
    return std::abs(area) / 2.0;
}

Polygon getFrame(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return Polygon{};

    auto compareX = [](const Point& a, const Point& b) { return a.x < b.x; };
    auto compareY = [](const Point& a, const Point& b) { return a.y < b.y; };

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (const auto& poly : polygons) {
        const auto [minXIt, maxXIt] = std::minmax_element(
            poly.points.begin(), poly.points.end(), compareX);
        const auto [minYIt, maxYIt] = std::minmax_element(
            poly.points.begin(), poly.points.end(), compareY);

        minX = std::min(minX, minXIt->x);
        maxX = std::max(maxX, maxXIt->x);
        minY = std::min(minY, minYIt->y);
        maxY = std::max(maxY, maxYIt->y);
    }

    return Polygon{{minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY}};
}

bool isInside(const Polygon& poly, const Polygon& frame) {
    if (frame.points.size() != 4) return false;

    const auto& [minX, minY] = frame.points[0];
    const auto& [maxX, maxY] = frame.points[2];

    return std::all_of(poly.points.begin(), poly.points.end(),
        [minX, maxX, minY, maxY](const Point& p) {
            return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
        });
}

void areaCommand(const std::vector<Polygon>& polygons,
                std::istream& in, std::ostream& out) {
    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    std::string arg;
    in >> arg;

    auto condition = [](const Polygon&) { return true; };

    if (arg == "EVEN") {
        condition = [](const Polygon& p) { return p.points.size() % 2 == 0; };
    } else if (arg == "ODD") {
        condition = [](const Polygon& p) { return p.points.size() % 2 != 0; };
    } else if (arg == "MEAN") {
        if (polygons.empty()) {
            throw std::invalid_argument("No polygons");
        }
        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + getArea(p); });
        out << total / polygons.size();
        return;
    } else {
        size_t num = std::stoul(arg);
        if (num < 3) throw std::invalid_argument("Invalid vertex count");
        condition = [num](const Polygon& p) { return p.points.size() == num; };
    }

    double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [&condition](double sum, const Polygon& p) {
            return condition(p) ? sum + getArea(p) : sum;
        });
    out << total;
}

void maxCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out) {
    if (polygons.empty()) throw std::invalid_argument("No polygons");

    std::string arg;
    in >> arg;

    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    if (arg == "AREA") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return getArea(a) < getArea(b);
            });
        out << getArea(*it);
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        out << it->points.size();
    } else {
        throw std::invalid_argument("Invalid argument");
    }
}

void minCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out) {
    if (polygons.empty()) throw std::invalid_argument("No polygons");

    std::string arg;
    in >> arg;

    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    if (arg == "AREA") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return getArea(a) < getArea(b);
            });
        out << getArea(*it);
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        out << it->points.size();
    } else {
        throw std::invalid_argument("Invalid argument");
    }
}

void countCommand(const std::vector<Polygon>& polygons,
                 std::istream& in, std::ostream& out) {
    std::string arg;
    in >> arg;

    size_t count = 0;

    if (arg == "EVEN") {
        count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 == 0; });
    } else if (arg == "ODD") {
        count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 != 0; });
    } else {
        size_t num = std::stoul(arg);
        if (num < 3) throw std::invalid_argument("Invalid vertex count");
        count = std::count_if(polygons.begin(), polygons.end(),
            [num](const Polygon& p) { return p.points.size() == num; });
    }
    out << count;
}

void rmEchoCommand(std::vector<Polygon>& polygons,
                  std::istream& in, std::ostream& out) {
    Polygon target;
    in >> target;
    if (!in) throw std::invalid_argument("Invalid polygon");

    size_t removed = 0;
    auto it = polygons.begin();
    while (it != polygons.end()) {
        if (*it == target && it + 1 != polygons.end() && *(it + 1) == target) {
            it = polygons.erase(it + 1);
            ++removed;
        } else {
            ++it;
        }
    }
    out << removed;
}

void inframeCommand(const std::vector<Polygon>& polygons,
                   std::istream& in, std::ostream& out) {
    Polygon target;
    in >> target;
    if (!in) throw std::invalid_argument("Invalid polygon");

    Polygon frame = getFrame(polygons);
    out << (isInside(target, frame) ? "<TRUE>" : "<FALSE>");
}

void rightshapesCommand(const std::vector<Polygon>& polygons,
                       std::ostream& out) {
    auto isRightAngle = [](const Polygon& poly) {
        if (poly.points.size() < 3) return false;

        for (size_t i = 0; i < poly.points.size(); ++i) {
            const Point& a = poly.points[i];
            const Point& b = poly.points[(i + 1) % poly.points.size()];
            const Point& c = poly.points[(i + 2) % poly.points.size()];

            int dx1 = b.x - a.x;
            int dy1 = b.y - a.y;
            int dx2 = c.x - b.x;
            int dy2 = c.y - b.y;

            if (dx1 * dx2 + dy1 * dy2 == 0) return true;
        }
        return false;
    };

    out << std::count_if(polygons.begin(), polygons.end(), isRightAngle);
}

IOFmtGuard::IOFmtGuard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}

IOFmtGuard::~IOFmtGuard() {
    s_.precision(precision_);
    s_.flags(flags_);
}

} // namespace ilyaerofick

int main(int argc, char* argv[]) {
    using namespace ilyaerofick;

    if (argc != 2) {
        std::cerr << "Wrong arguments\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "File not open\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    using InputIt = std::istream_iterator<Polygon>;
    while (!in.eof()) {
        std::copy(InputIt{in}, InputIt{}, std::back_inserter(polygons));
        if (in.fail() && !in.eof()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    in.close();

    std::map<std::string,
        std::function<void(std::istream&, std::ostream&)>> commands;
    using namespace std::placeholders;

    commands["AREA"] = std::bind(areaCommand, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(maxCommand, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(minCommand, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(countCommand, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmEchoCommand, std::ref(polygons), _1, _2);
    commands["INFRAME"] = std::bind(inframeCommand, std::cref(polygons), _1, _2);
    commands["RIGHTSHAPES"] =
        std::bind(rightshapesCommand, std::cref(polygons), _2);

    std::string cmd;
    while (std::cin >> cmd) {
        try {
            auto it = commands.find(cmd);
            if (it != commands.end()) {
                it->second(std::cin, std::cout);
            } else {
                throw std::invalid_argument("Invalid command");
            }
            std::cout << "\n";
        } catch (const std::exception&) {
            std::cout << "<INVALID COMMAND>\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}