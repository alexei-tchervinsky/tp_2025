#include <iostream>
#include <sstream>
#include "DataStruct.hpp"
#include "IO_Objects.hpp"

using namespace prokopenko;

int main() {
    DataStruct ds;
    while (std::cin >> ds) {
        std::cout << ds << std::endl;
    }
    return 0;
}
