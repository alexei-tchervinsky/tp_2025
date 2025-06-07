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

    while (!std::cin.eof())
    {
        std::istream_iterator<DataStruct> it(std::cin);
        std::istream_iterator<DataStruct> end;

        if (it != end)
        {
            std::copy(it, end, std::back_inserter(ds));
        }

        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (std::cin.eof())
            break;
    }

    std::sort(ds.begin(), ds.end(), orlov::compareDataStruct);

    std::copy
    (
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

