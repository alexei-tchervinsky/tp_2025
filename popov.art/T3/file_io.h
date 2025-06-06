#ifndef FILE_IO_H
#define FILE_IO_H
#include "geometry.h"
#include <vector>
#include <string>
bool isValidPolygon(const Polygon& p);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
Polygon parsePolygon(const std::string& input);
#endif // FILE_IO_H
