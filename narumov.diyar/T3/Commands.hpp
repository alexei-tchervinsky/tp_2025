#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

#include "DataStructs.hpp"

namespace narumov {
    extern std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>> commandsList;
    void executeCommand(const std::vector<Polygon>&, std::istream&, std::ostream&);

    void calcAreaSum(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void countPolygons(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void findMinimum(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void findMaximum(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void findMaxSequence(const std::vector<Polygon>&, std::istream&, std::ostream&);
    void checkInsideFrame(const std::vector<Polygon>&, std::istream&, std::ostream&);
}

#endif
