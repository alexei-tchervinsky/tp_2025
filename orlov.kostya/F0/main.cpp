#include <iostream>
#include <string>
#include "graph.hpp"
#include "kruscal.hpp"
#include "prim.hpp"
#include "struct.hpp"
#include "commands.hpp"

int main()
{
    while (!std::cin.eof())
    {
        std::cout << "List of commands:\n";
        std::cout
            << "\tGRAPH: test for Graph\n"
            << "\tKRUSCAL: test for Kruscal algorithm\n"
            << "\tPRIM: test for Prim algorithm\n"
            << "\tKRUSCAL AND PRIM IND MST: test for Kruscal and Prim algorithm with indentical MST\n"
            << "\tKRUSCAL AND PRIM DIFF MST: test for Kruscal and Prim algorithm with diffrent MST\n"
            ;

        std::cout << "Please, enter command from list:\n";

        std::string line;
        if (!std::getline(std::cin, line)) break;

        executeCommand(line);
    }

    return 0;
}

