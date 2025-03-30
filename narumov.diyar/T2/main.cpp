#include "DataStruct.hpp"

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using narumov::DataStruct;

int main() {
    std::vector<DataStruct> ds;
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(ds)
    );
    std::sort(ds.begin(), ds.end(), narumov::compareDataStruct);
    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
