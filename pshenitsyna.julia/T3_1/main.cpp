#include <iostream>
#include <vector>
#include "Struct.h"
#include "helpFunctions.h"

// 5 вариант: 1 команда: ECHO 2 команда: INFRAME

using namespace wheatman;

int main(int args, char* argv[]) {
    if (args != 2 || argv[0] == nullptr)
    {
        std::cerr << "Error. Use ./lab filename\n";
        return 1;
    }
    std::string filename = argv[1];
    std::vector<Polygon> geometry = readFile(filename);

    std::string command;
    while (std::getline(std::cin, command))
    {
        if(std::cin.eof()) break;
        CommandsHandler(command, geometry);
    }
    return 0;
}
