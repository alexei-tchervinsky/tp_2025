#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "iofmtguard.h"
#include "DataStruct.h"

int main() {
    using namespace solution;

    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> inputIt(std::cin);
    std::istream_iterator<DataStruct> eos;

    std::copy(inputIt, eos, std::back_inserter(data));

    if (data.empty()) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    std::sort(data.begin(), data.end());

    std::ostream_iterator<DataStruct> outputIt(std::cout, "\n");
    std::copy(data.begin(), data.end(), outputIt);

    return 0;
}
