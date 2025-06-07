#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.hpp"

using orlov::DataStruct;

int main()
{
    std::vector<DataStruct> ds;

    while (true)
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(ds)
        );

        if (std::cin.eof())
        {
            break;
        }
        else if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(ds.begin(), ds.end(), orlov::compareDataStruct);

    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

