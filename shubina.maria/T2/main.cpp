#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // добавлено для setprecision

#include "DataStruct.h"
#include "IO_Objects.h"
#include "iofmtguard.h"

int main() {
    iofmtguard guard(std::cout);

    std::cout << std::fixed << std::setprecision(1);

    std::cerr << "Enter records:\n";

    std::vector<DataStruct> data = readDataStructs(std::cin);
    std::sort(data.begin(), data.end());

    std::cerr << "Sorted output:\n";
    writeDataStructs(data, std::cout);

    return 0;
}

