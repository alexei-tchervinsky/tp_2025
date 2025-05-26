#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include "Polygon.hpp"
#include "Commands.hpp"

using namespace ponomarenko;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Polygon p;
        if (!(iss >> p)) {
            continue;
        }

        iss >> std::ws;

        if (!iss.eof()) {
            continue;
        }

        polygons.push_back(std::move(p));
    }

    std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&)>> commands = {
        {"AREA", areaCommand},
        {"COUNT", countCommand},
        {"MAX", maxCommand},
        {"MIN", minCommand},
        {"LESSAREA", lessAreaCommand},
        {"MAXSEQ", maxSeqCommand}
      };

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        auto it = commands.find(command);
        if (it != commands.end()) {
            it->second(polygons, iss);
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
