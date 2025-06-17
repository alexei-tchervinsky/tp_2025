#include "iofmtguard.h"
#include "commands.h"
#include "DataStruct.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>

namespace shubina {
    namespace {
        void checkEmpty(const std::vector<Polygon>& polygons) {
            if (polygons.empty()) {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }

        bool isValidPolygon(const Polygon& poly) {
            return poly.points.size() >= 3;
        }

        void calculateFrameBounds(const std::vector<Polygon>& polygons,
                                int& min_x, int& max_x,
                                int& min_y, int& max_y) {
            min_x = std::numeric_limits<int>::max();
            max_x = std::numeric_limits<int>::min();
            min_y = std::numeric_limits<int>::max();
            max_y = std::numeric_limits<int>::min();

            for (const auto& poly : polygons) {
                for (const auto& point : poly.points) {
                    if (point.x < min_x) min_x = point.x;
                    if (point.x > max_x) max_x = point.x;
                    if (point.y < min_y) min_y = point.y;
                    if (point.y > max_y) max_y = point.y;
                }
            }
        }
    }

    // [Остальные функции остаются без изменений...]

    void inframeCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        Polygon target;
        std::string inputLine;
        std::getline(in, inputLine);

        if (inputLine.empty()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        std::istringstream iss(inputLine);
        if (!(iss >> target)) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        // Дополнительная проверка на оставшиеся данные в строке
        std::string remaining;
        if (iss >> remaining) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        // Проверка на минимальное количество точек
        if (target.points.size() < 3) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        // Фильтрация валидных полигонов
        std::vector<Polygon> validPolygons;
        for (const auto& poly : polygons) {
            if (isValidPolygon(poly)) {
                validPolygons.push_back(poly);
            }
        }

        if (validPolygons.empty()) {
            out << "<FALSE>\n";
            return;
        }

        // Вычисление границ фрейма
        int frame_min_x, frame_max_x, frame_min_y, frame_max_y;
        calculateFrameBounds(validPolygons, frame_min_x, frame_max_x, frame_min_y, frame_max_y);

        // Проверка всех точек целевого полигона
        bool allInside = true;
        for (const auto& point : target.points) {
            if (point.x < frame_min_x || point.x > frame_max_x ||
                point.y < frame_min_y || point.y > frame_max_y) {
                allInside = false;
                break;
            }
        }

        out << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
}

