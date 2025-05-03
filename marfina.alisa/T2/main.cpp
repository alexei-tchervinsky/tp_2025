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
        marfina::DataStruct temp;
        if (std::cin >> temp)
        {
            data.push_back(temp);
        }
        else if (!std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (data.empty())
    {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<marfina::DataStruct>(std::cout, "\n")
    );
    return 0;
}
