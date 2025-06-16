#include "data_struct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <limits>

int main() {
    std::vector<shubina::DataStruct> data;
    while(!std::cin.eof())
    {
        std::copy(
        std::istream_iterator<shubina::DataStruct >(std::cin),
        std::istream_iterator<shubina::DataStruct >(),
        std::back_inserter(data));
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }


    std::sort(data.begin(), data.end(), shubina::compare_structures);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<shubina::DataStruct>(std::cout, "\n")
    );

    return 0;
}
