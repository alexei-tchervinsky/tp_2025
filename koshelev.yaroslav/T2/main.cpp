#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"
int main() {
    std::vector<solution::DataStruct> records;
    solution::DataStruct temp;
    while (std::cin.peek() != EOF) {
        if (std::cin >> temp) {
            records.push_back(temp);
        } else {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(records.begin(), records.end());
    for (const auto& entry : records) {
        std::cout << entry << '\n';
    }
    return 0;
}
