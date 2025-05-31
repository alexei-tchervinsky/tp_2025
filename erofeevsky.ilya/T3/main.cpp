#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <limits>
#include "geometry.hpp"
#include "iofmtguard.hpp"

int main(int argc, char* argv[]) {
    using namespace ilyaerofick;

    if (argc != 2) {
        std::cerr << "Wrong arguments\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "File not open\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    while (!in.eof()) {
        Polygon p;
        in >> p;
        if (in) {
            polygons.push_back(p);
        } else {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    in.close();

    std::map<std::string,
        std::function<void(std::istream&, std::ostream&)>> commands;

    commands["AREA"] = [&polygons](std::istream& in, std::ostream& out) {
        areaCommand(polygons, in, out);
    };
    commands["MAX"] = [&polygons](std::istream& in, std::ostream& out) {
        maxCommand(polygons, in, out);
    };
    commands["MIN"] = [&polygons](std::istream& in, std::ostream& out) {
        minCommand(polygons, in, out);
    };
    commands["COUNT"] = [&polygons](std::istream& in, std::ostream& out) {
        countCommand(polygons, in, out);
    };
    commands["RMECHO"] = [&polygons](std::istream& in, std::ostream& out) {
        rmEchoCommand(polygons, in, out);
    };
    commands["INFRAME"] = [&polygons](std::istream& in, std::ostream& out) {
        inframeCommand(polygons, in, out);
    };
    commands["RIGHTSHAPES"] = [&polygons](std::istream&, std::ostream& out) {
        rightshapesCommand(polygons, out);
    };

    std::string cmd;
    while (std::cin >> cmd) {
        try {
            auto it = commands.find(cmd);
            if (it != commands.end()) {
                it->second(std::cin, std::cout);
            } else {
                throw std::invalid_argument("Invalid command");
            }
            std::cout << "\n";
        } catch (const std::exception&) {
            std::cout << "<INVALID COMMAND>\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}