#ifndef T3_HELPFUNCTIONS_H
#define T3_HELPFUNCTIONS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Struct.h"

namespace wheatman
{
    Polygon splitPolygon(const std::string& str);
    std::vector<Polygon> readFile (const std::string & filename);
    void initializeCommands (std::vector<Polygon>& p);
    void CommandsHandler (const std::string& command, std::vector<Polygon>& polygons);
}
#endif //T3_HELPFUNCTIONS_H
