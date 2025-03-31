#include "DataStruct.hpp"

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>

using narumov::DataStruct;

int main() {
    std::vector<DataStruct> ds;
    while(!std::cin.eof()) {
        DataStruct temp;
        std::cin >> temp;
        if(!std::cin.fail()) {
            ds.push_back(temp);
            continue;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::sort(ds.begin(), ds.end(), narumov::compareDataStruct);
    std::copy(
        ds.begin(),
        ds.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
