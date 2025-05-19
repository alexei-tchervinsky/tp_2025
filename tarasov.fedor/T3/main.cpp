#include <map>
#include "command.hpp"

using CommandHandler = std::function<void(const std::vector<Polygon>&, std::stringstream&)>;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Используйте: ./lab filename" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> polygons = readFile(filename);

    std::map<std::string, CommandHandler> commands;

    commands["AREA"] = [&](const std::vector<Polygon>& p, std::stringstream& ss) {
        std::string sub_command;
        ss >> sub_command;
        areaCommand(p, sub_command);
    };
    commands["MAX"] = [&](const std::vector<Polygon>& p, std::stringstream& ss) {
        std::string sub_command;
        ss >> sub_command;
        maxCommand(p, sub_command);
    };
    commands["MIN"] = [&](const std::vector<Polygon>& p, std::stringstream& ss) {
        std::string sub_command;
        ss >> sub_command;
        minCommand(p, sub_command);
    };
    commands["COUNT"] = [&](const std::vector<Polygon>& p, std::stringstream& ss) {
        std::string sub_command;
        ss >> sub_command;
        countCommand(p, sub_command);
    };
    commands["PERMS"] = [&](const std::vector<Polygon>& p, std::stringstream& ss) {
        permsCommand(p, ss);
    };
    commands["RIGHTSHAPES"] = [&](const std::vector<Polygon>& p, std::stringstream&) {
        rightShapesCommand(p);
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);

        std::string command;
        ss >> command;

        auto it = commands.find(command);

        if (it != commands.end()) {
            it->second(polygons, ss);
        } else {
            bool empty = true;
            for (char c : line) {
                if (!std::isspace(static_cast<unsigned char>(c))) {
                    empty = false;
                    break;
                }
            }
            if (!empty && !command.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            } else if (empty && std::cin.eof()) {
                break;
            }
        }
        if (std::cin.eof()) {
            break;
        }
    }
    return 0;
}
