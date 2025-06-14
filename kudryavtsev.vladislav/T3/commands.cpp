#include "commands.hpp"
#include "read.hpp"
#include "COMBS.hpp"
#include <iostream>
#include <cctype>

using namespace vlad;

void processCommands(const std::vector<Polygon>& poly) {
    std::map<std::string, CommandHandler> commands;

    commands["AREA"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        std::string sub_command;
        input >> sub_command;
        area(p, sub_command);
    };
    commands["MAX"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        std::string sub_command;
        input >> sub_command;
        max(p, sub_command);
    };
    commands["MIN"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        std::string sub_command;
        input >> sub_command;
        min(p, sub_command);
    };
    commands["COUNT"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        std::string sub_command;
        input >> sub_command;
        count(p, sub_command);
    };
    commands["PERMS"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        perms(p, input);
    };
    commands["MAXSEQ"] = [&](const std::vector<Polygon>& p, std::stringstream& input) {
        maxSeq(p, input);
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream input(line);

        std::string command;
        input >> command;

        auto it = commands.find(command);

        if (it != commands.end()) {
            it->second(poly, input);
        }
        else {
            bool empty = true;
            for (char e : line) {
                if (!std::isspace(static_cast<unsigned char>(e))) {
                    empty = false;
                    break;
                }
            }
            if (!empty and !command.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
            else if (empty and std::cin.eof()) {
                break;
            }
        }
        if (std::cin.eof()) {
            break;
        }
    }
}

