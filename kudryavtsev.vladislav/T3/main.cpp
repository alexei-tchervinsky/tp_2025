#include "Structs.hpp"
#include "read.hpp"
#include "COMBS.hpp"
#include "commands.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace vlad;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect filename\n";
        exit(1);
    }

    std::vector<Polygon> poly = readFile(argv[1]);
    processCommands(poly);

    return 0;
<<<<<<< HEAD
}
=======
}

>>>>>>> c3d0a5c52e2440e7783d44543defe78b77b69bb8
