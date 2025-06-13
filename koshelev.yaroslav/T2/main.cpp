#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

int main() {
    using namespace nspace;

    std::vector<DataStruct> data;
    DataStruct temp;

    while (!std::cin.eof()) {
        if (std::cin >> temp) {
            data.push_back(temp);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(), compare);

    for (const auto& el : data) {
        std::cout << el << "\n";
    }

    return 0;
}
