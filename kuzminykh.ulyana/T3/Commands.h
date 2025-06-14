#include "Geometry.h"
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <map>

namespace kuzminykh
{
    double calculateArea(const Polygon& polygon);
    void area(const std::vector<Polygon>& polygons, const std::string& subcmd);
    void max(const std::vector<Polygon>& polygons, const std::string& subcmd);
    void min(const std::vector<Polygon>& polygons, const std::string& subcmd);
    void count(const std::vector<Polygon>& polygons, const std::string& subcmd);
    bool isPerm(const Polygon& p1, const Polygon& p2);
    void perms(const std::vector<Polygon>& polygons, std::stringstream& params);
    void inFrame(const std::vector<Polygon>& polygons, std::stringstream& params);

    void handleAreaCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    void handleMaxCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    void handleMinCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    void handleCountCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    void handlePermsCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    void handleInFrameCommand(const std::vector<Polygon>& polygons, std::stringstream& ss);
    std::map<std::string, std::function<void(const std::vector<Polygon>&, std::stringstream&)>> createCommandMap();
}
