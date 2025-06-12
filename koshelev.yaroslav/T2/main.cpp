#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"

int main() {
    std::vector<koshelev::DataStruct> data;
    koshelev::DataStruct temp;
    while (!std::cin.eof()) {
        if (std::cin >> temp) {
            data.push_back(temp);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end());
    for (const auto& el : data) {
        std::cout << el << "\n";
    }
    return 0;
}
