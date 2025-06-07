#include "DataStruct.hpp"
#include "LineIterator.hpp"
#include "DataStructIterator.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<myspace::DataStruct> ds;

    std::copy(datastruct_iterator(line_iterator(std::cin)),
              datastruct_iterator(),
              std::back_inserter(ds));

    std::sort(ds.begin(), ds.end(), myspace::compare);

    std::copy(ds.begin(), ds.end(),
              std::ostream_iterator<myspace::DataStruct>(std::cout, "\n"));

    return 0;
}

