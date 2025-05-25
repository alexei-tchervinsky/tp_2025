#include "Commands.hpp"
#include "Polygon.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <functional>
#include <algorithm>
#include <sstream>

namespace ponomarenko {

    void areaCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        std::string arg;
        in >> arg;

        iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1);
        if (arg == "EVEN") {
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return (p.points.size() % 2 == 0) ? acc + getArea(p) : acc;
            });
            std::cout << sum << "\n";
        } else if (arg == "ODD") {
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return (p.points.size() % 2 == 1) ? acc + getArea(p) : acc;
            });
            std::cout << sum << "\n";
        } else if (arg == "MEAN") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + getArea(p);
            });
            std::cout << total / polygons.size() << "\n";
        } else {
            std::istringstream iss(arg);
            size_t n = 0;
            if (!(iss >> n) || n < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [n](double acc, const Polygon& p) {
                return (p.points.size() == n) ? acc + getArea(p) : acc;
            });
            std::cout << sum << "\n";
        }
    }

    void countCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        std::string arg;
        in >> arg;
        if (arg == "EVEN") {
            size_t count = std::count_if(polygons.begin(), polygons.end(),
                [](const Polygon& p) {
                    return p.points.size() % 2 == 0;
                });
            std::cout << count << "\n";
        } else if (arg == "ODD") {
            size_t count = std::count_if(polygons.begin(), polygons.end(),
                [](const Polygon& p) {
                    return p.points.size() % 2 == 1;
                });
            std::cout << count << "\n";
        } else {
            std::istringstream iss(arg);
            size_t n = 0;
            if (!(iss >> n) || n < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            size_t count = std::count_if(polygons.begin(), polygons.end(),
                [n](const Polygon& p) {
                    return p.points.size() == n;
                });
            std::cout << count << "\n";
        }
    }

    void maxCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        std::string arg;
        in >> arg;
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        if (arg == "AREA") {
            iofmtguard guard(std::cout);
            std::cout << std::fixed << std::setprecision(1);

            double maxArea = getArea(*std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return getArea(a) < getArea(b);
                }));
            std::cout << maxArea << "\n";
        } else if (arg == "VERTEXES") {
            size_t maxVerts = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
            }) -> points.size();
            std::cout << maxVerts << "\n";
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    void minCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        std::string arg;
        in >> arg;
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1);

        if (arg == "AREA") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return getArea(a) < getArea(b);
            });
            std::cout << getArea(*it) << "\n";
        } else if (arg == "VERTEXES") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() <  b.points.size();
            });
            std::cout << it->points.size() << "\n";
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    void lessAreaCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        Polygon inputPolygon;
        if (!(in >> inputPolygon)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        in >> std::ws;
        if (in.peek() != std::char_traits<char>::eof() || inputPolygon.points.size() < 3) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        double areaRef = getArea(inputPolygon);
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [areaRef](const Polygon& p) {
                return getArea(p) < areaRef;
            });
        std::cout << count << "\n";

    }

    void maxSeqCommand(const std::vector<Polygon>& polygons, std::istream& in) {
        Polygon target;
        if (!(in >> target)) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        in >> std::ws;
        if (in.peek() != std::char_traits<char>::eof()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        std::pair<std::size_t, std::size_t> result = std::accumulate(
            polygons.begin(), polygons.end(), std::pair<std::size_t, std::size_t>{0, 0},
            [&target](std::pair<std::size_t, std::size_t> acc, const Polygon& p) {
                std::size_t current = (p == target) ? acc.first + 1 : 0;
                std::size_t max = std::max(acc.second, current);
                return std::pair<std::size_t, std::size_t>(current, max);
            }
        );
        std::cout << result.second << "\n";
    }
}
