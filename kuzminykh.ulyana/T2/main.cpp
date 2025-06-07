#include <algorithm>
#include "DataStructsIO.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <limits>

int main() {
    std::vector<DataStruct> ds;
    std::istream_iterator<DataStruct> it(std::cin), end;

    while (it != end) {
        ds.push_back(*it);
        ++it;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(ds.begin(), ds.end(), compareDataStructs);
    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
