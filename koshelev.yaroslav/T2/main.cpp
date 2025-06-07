#include "DataStruct.h"
#include "IO_Objects.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<DataStruct> data;

    try {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (data.empty()) {
            std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
            return 0;
        }

        std::sort(data.begin(), data.end(), compareDataStruct);

        std::copy(
            data.begin(),
            data.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n")
        );
    } catch (...) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
    }

    return 0;
}
