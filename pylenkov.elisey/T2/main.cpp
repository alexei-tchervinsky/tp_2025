#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

using nspace::DataStruct;

int main()
{
    std::vector<DataStruct> ds;

    while (true)
    {
        DataStruct temp;

        if (!(std::cin >> temp))
        {
            if (std::cin.eof())
            {
                break;
            }


            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        ds.push_back(temp);
    }

    std::sort(ds.begin(), ds.end(), nspace::compare);

    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
