#include "data_struct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main()
{
    shubina::iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    std::vector<shubina::DataStruct> data = shubina::readDataStructs(std::cin);

    if (data.empty())
    {
        std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    std::sort(data.begin(), data.end(), shubina::compare_structures);
    shubina::writeDataStructs(data, std::cout);

    return 0;
}

