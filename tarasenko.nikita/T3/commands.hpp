#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <map>
#include <functional>
#include <iosfwd>
#include "DataStruct.hpp"

namespace tarasenko {
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>;
    using CommandMap = std::map<std::string, CommandFunction>;

    CommandMap createCommandMap();

    void executeCommand(const CommandMap& commands,
        const std::vector<Polygon>& polygons,
        const std::string& command,
        std::istream& in,
        std::ostream& out);

    void areaCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void maxCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void minCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void countCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void rectsCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void sameCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void intersectionsCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void rmechoCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
}

#endif