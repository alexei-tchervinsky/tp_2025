#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"

int main() {
    std::vector<solution::DataStruct> records;
    solution::DataStruct temp;

    while (std::cin.peek() != EOF) {
        try {
            if (std::cin >> temp) {
                records.push_back(temp);
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } catch (const std::exception& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (records.empty()) {
        std::cout << "Нет корректных данных для обработки.\n";
        return 0;
    }

    std::sort(records.begin(), records.end());

    for (const auto& entry : records) {
        std::cout << entry << '\n';
    }

    return 0;
}
