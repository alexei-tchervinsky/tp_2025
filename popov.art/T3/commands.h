#ifndef COMMANDS_H
#define COMMANDS_H

#include "geometry.h"
#include <vector>
#include <string>

void processCommand(const std::string& command, std::vector<Polygon>& polygons);

#endif // COMMANDS_H
