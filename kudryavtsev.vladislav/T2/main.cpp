#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    std::vector<myspace::DataStruct> ds;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        myspace::DataStruct temp;

        if (iss >> temp) {
            ds.push_back(temp);
        }
    }
    std::sort(ds.begin(), ds.end(), myspace::compare);
    for (const auto& item : ds) {
        std::cout << item << "\n";
    }

    return 0;
}

