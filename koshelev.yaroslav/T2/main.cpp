#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

int main() {
    std::vector<solution::DataStruct> data;
    std::istream_iterator<solution::DataStruct> inputIt(std::cin), eos;
    std::copy_if(inputIt, eos, std::back_inserter(data), [](const solution::DataStruct&) {
        return !std::cin.fail();
    });
    std::cin.clear();
    std::sort(data.begin(), data.end());
    std::ostream_iterator<solution::DataStruct> outputIt(std::cout, "\n");
    std::copy(data.begin(), data.end(), outputIt);
    return 0;
}
