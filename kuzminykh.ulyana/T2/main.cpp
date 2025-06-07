#include <algorithm>
#include "DataStructsIO.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <limits>

using namespace kuzminykh;

int main()
{
    std::vector<DataStruct> ds;
    while (!std::cin.eof())
    {

        DataStruct data;
        std::cin >> data;

        if (!std::cin.fail())
        {
            ds.push_back(data);
            continue;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::sort(ds.begin(), ds.end(), compare);
    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
