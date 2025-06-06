#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include "polygon.hpp"

void processAreaCommand(const std::vector<Polygon>& polygons, const std::string& param);
void processMaxMinCommand(const std::vector<Polygon>& polygons, const std::string& cmd, const std::string& param);
void processCountCommand(const std::vector<Polygon>& polygons, const std::string& param);
void processRmechoCommand(std::vector<Polygon>& polygons, const std::string& line);
void processIntersectionsCommand(const std::vector<Polygon>& polygons, const std::string& line);

#endif // COMMANDS_HPP