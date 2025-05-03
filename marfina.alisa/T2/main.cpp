#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "data_struct.hpp"

int main()
{
    std::vector<marfina::DataStruct> data;
    while (!std::cin.eof())
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        marfina::DataStruct tmp;
        if (std::cin >> tmp)  // Removed the is_supported_input check
        {
            data.push_back(tmp);
        }
    }
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<marfina::DataStruct>(std::cout, "\n"));

    return 0;
}
