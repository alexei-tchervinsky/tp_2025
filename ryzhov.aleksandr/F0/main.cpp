#include <map>
#include <iosfwd>
#include <stdexcept>
#include <iostream>
#include <limits>

#include "command.hpp"


using namespace ryzhov;

int main() {
    ERDictionary dictionary;
    auto commands = createCommandMap();

    std::string command;
    while (std::cin >> command) {
        try {
            executeCommand(commands, dictionary, command, std::cin, std::cout);
        }
        catch (const std::invalid_argument &e) {
            std::cout << "<INVALID COMMAND>\n";
            if (std::string(e.what()) == "UNKNOWN COMMAND") {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    return 0;
}
