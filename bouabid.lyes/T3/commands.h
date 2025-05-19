#ifndef COMMANDS_H
#define COMMANDS_H

#include "geometry.h"
#include <vector>

size_t handleEcho(std::vector<Polygon>& polygons, const Polygon& target);
bool handleInFrame(const std::vector<Polygon>& polygons, const Polygon& target);

#endif
