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
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        marfina::DataStruct tmp;
        if (std::cin >> tmp && marfina::is_supported_input(tmp))
        {
            data.push_back(tmp);
            has_supported = true;
        }
    }

    if (!has_supported)
    {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<marfina::DataStruct>(std::cout, "\n"));

    return 0;
}