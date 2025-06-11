#include <iostream>
#include <vector>
#include <algorithm>
#include "data_struct.h"

int main()
{
    try
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
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred.\n";
        return 1;
    }

    return 0;
}

