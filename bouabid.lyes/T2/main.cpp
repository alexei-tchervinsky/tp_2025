#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

int main() {
    std::vector<DataStruct> dataVec;

    std::istream_iterator<DataStruct> it(std::cin), end;
    std::copy_if(it, end, std::back_inserter(dataVec), [](const DataStruct&) {
        return true;
    });

    std::sort(dataVec.begin(), dataVec.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    });

    std::ostream_iterator<DataStruct> out_it(std::cout, "\n");
    std::copy(dataVec.begin(), dataVec.end(), out_it);

    return 0;
}
