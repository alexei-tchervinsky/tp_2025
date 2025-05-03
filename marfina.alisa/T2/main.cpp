#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include <sstream>
#include "data_struct.hpp"

int main()
{
    std::vector<marfina::DataStruct> data;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::istringstream iss(line);
        marfina::DataStruct temp;
        if (iss >> temp)
        {
            data.push_back(temp);
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
