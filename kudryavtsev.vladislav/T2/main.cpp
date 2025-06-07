//CMP LSP and ULL BIN//

#include "DataStruct.hpp"

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

using myspace::DataStruct;

int main() {
    std::vector<DataStruct> ds;
    while(!std::cin.eof()) {
        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(ds));
        if(!std::cin.fail()) continue;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::sort(ds.begin(), ds.end(), myspace::compare);
    std::copy(ds.begin(), ds.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}

