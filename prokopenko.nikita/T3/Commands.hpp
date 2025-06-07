#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

namespace prokopenko {
    void areaCommand(const std::vector<Polygon>&, std::istream&);
    void countCommand(const std::vector<Polygon>&, std::istream&);
    void maxCommand(const std::vector<Polygon>&, std::istream&);
    void minCommand(const std::vector<Polygon>&, std::istream&);
    void lessAreaCommand(const std::vector<Polygon>&, std::istream&);
    void maxSeqCommand(const std::vector<Polygon>&, std::istream&);
}

#endif
