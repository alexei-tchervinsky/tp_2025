#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::vector<DataStruct> v;
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(v));
    std::sort(v.begin(), v.end());
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<DataStruct>(std::cout,"\n"));
    return 0;
}
