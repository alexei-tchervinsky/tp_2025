#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>

// Команды подсчёта по заданной фигуре
void doSAME(const Polygon& poly, const std::vector<Polygon>& shapes);
void doPERMS(const Polygon& poly, const std::vector<Polygon>& shapes);
void doEQUAL(const Polygon& poly, const std::vector<Polygon>& shapes);
void doCOUNT(const Polygon& poly, const std::vector<Polygon>& shapes);

#endif // COMMANDS_HPP
