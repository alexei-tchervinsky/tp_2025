#include <algorithm>

#include "DataStruct.hpp"

#include <vector>
#include <iostream>
#include <iterator>
#include <limits>

using namespace likhodievskii;

int main() {
    std::vector<DataStruct> ds;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>{std::cin},
            std::istream_iterator<DataStruct>(),
            std::back_inserter(ds)
        );
        if (!std::cin.fail()) {
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
