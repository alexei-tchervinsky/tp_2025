#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "DataStruct.h"
#include "IO_Objects.h"
#include "iofmtguard.h"

int main() {
    iofmtguard guard(std::cout);

    std::cout << std::fixed << std::setprecision(1);

    std::cerr << "Enter records:\n";

    std::vector<DataStruct> data = readDataStructs(std::cin);
    if (data.empty()) {
        std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    std::sort(data.begin(), data.end());

    std::cerr << "Sorted output:\n";
    writeDataStructs(data, std::cout);

    return 0;
}

