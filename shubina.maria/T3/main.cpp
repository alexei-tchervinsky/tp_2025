// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>

#include "Polygon.h"
#include "GeometryUtils.h"

using namespace std;
using namespace std::placeholders;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Error: No input file provided.\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: Cannot open file.\n";
        return 1;
    }

    vector<Polygon> polygons;
    string line;

    while (getline(fin, line)) {
        istringstream iss(line);
        Polygon poly;
        if (iss >> poly) {
            polygons.push_back(poly);
        }
    }

    cout << fixed << setprecision(1);

    string command;
    while (cin >> command) {
        if (command == "AREA") {
            string param;
            cin >> param;

            if (param == "ODD" || param == "EVEN") {
                bool isOdd = (param == "ODD");
                double total = accumulate(
                    polygons.begin(), polygons.end(), 0.0,
                    [isOdd](double sum, const Polygon& p) {
                        return (p.points.size() % 2 == (isOdd ? 1 : 0)) ? sum + getArea(p) : sum;
                    });
                cout << total << "\n";

            } else if (param == "MEAN") {
                if (polygons.empty()) {
                    cout << "<INVALID COMMAND>\n";
                    continue;
                }
                double total = accumulate(
                    polygons.begin(), polygons.end(), 0.0,
                    [](double sum, const Polygon& p) { return sum + getArea(p); });

                cout << total / polygons.size() << "\n";

            } else if (isdigit(param[0])) {
                int n = stoi(param);
                double total = accumulate(
                    polygons.begin(), polygons.end(), 0.0,
                    [n](double sum, const Polygon& p) {
                        return (p.points.size() == n) ? sum + getArea(p) : sum;
                    });
                cout << total << "\n";

            } else {
                cout << "<INVALID COMMAND>\n";
            }

        } else if (command == "MAX" || command == "MIN") {
            if (polygons.empty()) {
                cout << "<INVALID COMMAND>\n";
                continue;
            }

            string type;
            cin >> type;

            if (type == "AREA") {
                auto it = (command == "MAX")
                    ? max_element(polygons.begin(), polygons.end(),
                                  [](const Polygon& a, const Polygon& b) {
                                      return getArea(a) < getArea(b);
                                  })
                    : min_element(polygons.begin(), polygons.end(),
                                  [](const Polygon& a, const Polygon& b) {
                                      return getArea(a) < getArea(b);
                                  });

                cout << getArea(*it) << "\n";

            } else if (type == "VERTEXES") {
                auto it = (command == "MAX")
                    ? max_element(polygons.begin(), polygons.end(),
                                  [](const Polygon& a, const Polygon& b) {
                                      return a.points.size() < b.points.size();
                                  })
                    : min_element(polygons.begin(), polygons.end(),
                                  [](const Polygon& a, const Polygon& b) {
                                      return a.points.size() < b.points.size();
                                  });

                cout << it->points.size() << "\n";

            } else {
                cout << "<INVALID COMMAND>\n";
            }

        } else if (command == "COUNT") {
            string param;
            cin >> param;

            if (param == "ODD" || param == "EVEN") {
                bool isOdd = (param == "ODD");
                int count = count_if(polygons.begin(), polygons.end(),
                                     [isOdd](const Polygon& p) {
                                         return (p.points.size() % 2 == (isOdd ? 1 : 0));
                                     });
                cout << count << "\n";

            } else if (isdigit(param[0])) {
                int n = stoi(param);
                int count = count_if(polygons.begin(), polygons.end(),
                                     [n](const Polygon& p) {
                                         return p.points.size() == n;
                                     });
                cout << count << "\n";

            } else {
                cout << "<INVALID COMMAND>\n";
            }

        } else if (command == "PERMS") {
            Polygon target;
            cin >> target;

            int count = count_if(polygons.begin(), polygons.end(),
                                 [&target](const Polygon& p) {
                                     return isSamePolygon(p, target);
                                 });

            cout << count << "\n";

        } else if (command == "INFRAME") {
            Polygon testPoly;
            cin >> testPoly;

            if (polygons.empty()) {
                cout << "<FALSE>\n";
                continue;
            }

            int minX = INT_MAX, minY = INT_MAX;
            int maxX = INT_MIN, maxY = INT_MIN;

            for (const auto& poly : polygons) {
                for (const auto& p : poly.points) {
                    minX = min(minX, p.x);
                    minY = min(minY, p.y);
                    maxX = max(maxX, p.x);
                    maxY = max(maxY, p.y);
                }
            }

            bool inside = true;
            for (const auto& p : testPoly.points) {
                if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY) {
                    inside = false;
                    break;
                }
            }

            cout << (inside ? "<TRUE>" : "<FALSE>") << "\n";

        } else {
            cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}

