#ifndef T3_COMANDS_H
#define T3_COMANDS_H
#include "helpFunctions.h"
#include "Struct.h"

namespace wheatman
{
    double calculateArea(const Polygon& polygon); // подсчёт площади для использования в area
    void area (std::vector<Polygon> polygon, std::string& parameter); // у площади есть несколько вариантов параметра
    void max (std::vector<Polygon> polygon, std::string& parameter);
    void min (std::vector<Polygon> polygon, std::string& parameter);
    void count (std::vector<Polygon> polygon, std::string& parameter);
    size_t echo (std::vector<Polygon>& polygon, const Polygon& figure);
    bool inframe (std::vector<Polygon>& polygon, const Polygon& figure);
}

#endif //T3_COMANDS_H
