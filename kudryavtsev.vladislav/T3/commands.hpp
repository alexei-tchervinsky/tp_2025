#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include "Structs.hpp"

using CommandHandler = std::function<void(const std::vector<vlad::Polygon>&, std::stringstream&)>;

void processCommands(const std::vector<vlad::Polygon>& poly);

#endif

