#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::vector<DataStruct> records;
    std::size_t linesRead = 0;
    for (std::string dummy; std::getline(std::cin, dummy); ++linesRead)
    {
        std::istringstream tmp(dummy);
        DataStruct ds;
        if (tmp >> ds) records.push_back(std::move(ds));
    }
    if (records.empty())
    {
        if (linesRead == 0)
            std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        else
            std::cout << "Atleast one supported record type\n";
        return 0;
    }
    std::sort(records.begin(), records.end());
    std::copy(records.begin(), records.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
