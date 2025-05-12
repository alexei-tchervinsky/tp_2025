#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

int main() {
    using erofick::DataStruct;

    std::vector<DataStruct> data;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
        if (!std::cin.fail()) {
            continue;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::sort(data.begin(), data.end(), erofick::compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
