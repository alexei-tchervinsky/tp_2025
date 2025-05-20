#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <cctype>         
static bool hasVisibleChars(const std::string& s)
{
    return std::any_of(s.begin(), s.end(),
                        [](unsigned char c){ return !std::isspace(c); });
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::vector<DataStruct> records;
    std::size_t nonEmptyLines = 0;        
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (hasVisibleChars(line))
            ++nonEmptyLines;               
        std::istringstream tmp(line);
        DataStruct ds;                     
        if (tmp >> ds)                      
            records.push_back(std::move(ds));
    }
    if (records.empty())
    {
        if (nonEmptyLines == 0)
            std::cout << "Looks like there is no supported record. "
                        "Cannot determine input. Test skipped\n";
        else
            std::cout << "Atleast one supported record type\n";
        return 0;
    }
    std::sort(records.begin(), records.end());
    std::copy(records.begin(), records.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
