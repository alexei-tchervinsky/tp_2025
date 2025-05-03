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
        std::copy
        (
            std::istream_iterator<marfina::DataStruct>(std::cin),
            std::istream_iterator<marfina::DataStruct>(),
            std::back_inserter(data)
        );
         if (std::cin.fail())
         {
            continue;
         }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::copy
    (
        data.begin(),
        data.end(),
        std::ostream_iterator<marfina::DataStruct>(std::cout, "\n")
    );
    return 0;
}
