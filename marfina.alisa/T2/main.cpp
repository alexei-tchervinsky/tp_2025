#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "data_struct.hpp"

int main()
{
    std::vector<marfina::DataStruct> data;
    bool has_supported = false;
    while (!std::cin.eof())
    {
        marfina::DataStruct tmp;
        if (std::cin >> tmp)
        {
            data.push_back(tmp);
            has_supported = true;
        }
        else if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (!has_supported)
    {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::cout << "Atleast one supported record type\n";
    for (const auto& item : data)
    {
        std::cout << item << "\n";
    }
    return 0;
}
