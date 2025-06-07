#include "DataStructsIO.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

int main()
{
    std::vector<DataStruct> v;

    while (true)
    {
        DataStruct tmp;
        if (std::cin >> tmp)
        {
            v.push_back(tmp);
        }
        else
        {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(v.begin(), v.end(), [](const DataStruct& a, const DataStruct& b)
        {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
        });

    for (const auto& ds : v)
    {
        std::cout << ds << "\n";
    }

    return 0;
}
