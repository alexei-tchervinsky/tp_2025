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
        if (std::cin >> tmp)
        {
            data.push_back(tmp);
        }
    }
    if (data.empty())
    {
        std::cout << "Atleast one supported record type\n";
    }
    std::sort(data.begin(), data.end(), marfina::compare_structures);
    for (const auto& item : data)
    {
        std::cout << item << "\n";
    }

    return 0;
}
