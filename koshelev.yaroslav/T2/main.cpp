#include "DataStruct.h"
#include "IO_Objects.h"
#include <vector>
#include <algorithm>
#include <limits> 
#include <iostream>

int main() {
    std::vector<DataStruct> data;
    DataStruct temp;

    while (std::cin >> temp) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        data.push_back(temp);
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    for (const auto& item : data) {
        std::cout << item << '\n';
    }

    return 0;
}
