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
    using InputIt = std::istream_iterator<Polygon>;
    while (!in.eof()) {
        std::copy(InputIt{in}, InputIt{}, std::back_inserter(polygons));
        if (in.fail() && !in.eof()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    in.close();
    
    std::map<std::string, 
        std::function<void(std::istream&, std::ostream&)>> commands;
    using namespace std::placeholders;
    
    commands["AREA"] = std::bind(areaCommand, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(maxCommand, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(minCommand, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(countCommand, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmEchoCommand, std::ref(polygons), _1, _2);
    commands["INFRAME"] = std::bind(inframeCommand, std::cref(polygons), _1, _2);
    commands["RIGHTSHAPES"] = 
        std::bind(rightshapesCommand, std::cref(polygons), _2);
    
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
