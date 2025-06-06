#ifndef T3_1_COMANDS_H
#define T3_1_COMANDS_H
#include "helpFunctions.h"
#include "Struct.h"

namespace wheatman
{
    double calculateArea(const Polygon& polygon);
    void area (std::vector<Polygon> polygon, std::string& parameter);
    void max (std::vector<Polygon> polygon, std::string& parameter);
    void min (std::vector<Polygon> polygon, std::string& parameter);
    void count (std::vector<Polygon> polygon, std::string& parameter);
    size_t echo (std::vector<Polygon>& polygon, const Polygon& figure);
    bool inframe (std::vector<Polygon>& polygon, const Polygon& figure);
}

#endif //T3_1_COMANDS_H
