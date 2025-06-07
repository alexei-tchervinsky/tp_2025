#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

int main() {
    std::vector<std::string> lines{
        std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>()
    };

    std::vector<nspace::DataStruct> ds = std::accumulate(
        lines.begin(), lines.end(),
        std::vector<nspace::DataStruct>{},
        [](std::vector<nspace::DataStruct> acc, const std::string& line) {
            std::istringstream iss(line);
            nspace::DataStruct temp;

            if (iss >> temp) {
                acc.push_back(temp);
            }
            return acc;
        }
    );

    std::sort(ds.begin(), ds.end(), nspace::compare);

    std::copy(ds.begin(), ds.end(),
              std::ostream_iterator<nspace::DataStruct>(std::cout, "\n"));

    return 0;
}
