#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "DataStruct.hpp"
#include <functional>
#include <iosfwd>
#include <map>
#include <vector>

namespace evdokimov {
using CommandFunction =
    std::function<void(std::vector<Polygon> &, std::istream &, std::ostream &)>;

using CommandMap = std::map<std::string, CommandFunction>;

CommandMap createCommandMap();

void executeCommand(const CommandMap &commands, std::vector<Polygon> &polygons,
                    const std::string &command, std::istream &in,
                    std::ostream &out);

void areaCommand(std::vector<Polygon> &polygons, std::istream &in,
                 std::ostream &out);
void maxCommand(std::vector<Polygon> &polygons, std::istream &in,
                std::ostream &out);
void minCommand(std::vector<Polygon> &polygons, std::istream &in,
                std::ostream &out);
void countCommand(std::vector<Polygon> &polygons, std::istream &in,
                  std::ostream &out);
void rmechoCommand(std::vector<Polygon> &polygons, std::istream &in,
                   std::ostream &out);
void sameCommand(std::vector<Polygon> &polygons, std::istream &in,
                 std::ostream &out);
} // namespace evdokimov
#endif // COMMANDS_HPP
