#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

int main() {
    std::vector<DataStruct> dataVector;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    if (dataVector.empty()) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    auto compare = [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    };

    std::sort(dataVector.begin(), dataVector.end(), compare);

    std::copy(
        dataVector.begin(),
        dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

