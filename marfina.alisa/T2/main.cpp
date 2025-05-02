// main.cpp (исправленная версия)
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

int main()
{
    std::vector<marfina::DataStruct> data;
    std::copy
    (
        std::istream_iterator<marfina::DataStruct>(std::cin),
        std::istream_iterator<marfina::DataStruct>(),
        std::back_inserter(data)
    );
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::copy
    (
        data.begin(),
        data.end(),
        std::ostream_iterator<marfina::DataStruct>(std::cout, "\n")
    );
    return 0;
}
