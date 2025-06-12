#include "DataStruct.h"
#include "IO_Objects.h"
#include "iofmtguard.h"
#include <iostream>
#include <vector>

int main() {
    solution::iofmtguard guard(std::cout);
    std::vector<solution::DataStruct> data;

    solution::readData(std::cin, data);

    if (data.empty()) {
        std::cout << "No valid data found.\n";
        return 0;
    }

    solution::sortData(data);
    solution::writeData(std::cout, data);

    return 0;
}

