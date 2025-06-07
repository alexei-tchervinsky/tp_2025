#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<nspace::DataStruct> ds;

    std::istream_iterator<nspace::DataStruct> input_iter(std::cin);
    std::istream_iterator<nspace::DataStruct> end_iter;

    std::copy(input_iter, end_iter, std::back_inserter(ds));

    std::sort(ds.begin(), ds.end(), nspace::compare);

    std::ostream_iterator<nspace::DataStruct> output_iter(std::cout, "\n");
    std::copy(ds.begin(), ds.end(), output_iter);

    return 0;
}
