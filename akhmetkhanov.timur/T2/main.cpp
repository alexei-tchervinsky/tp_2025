#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    std::vector<nspace::DataStruct> ds;
    std::string line;

    // Чтение данных построчно
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        nspace::DataStruct temp;

        // Пытаемся распарсить строку
        if (iss >> temp) {
            ds.push_back(temp);
        }
        // Если парсинг не удался, строка игнорируется
    }

    // Сортировка данных
    std::sort(ds.begin(), ds.end(), nspace::compare);

    // Вывод результатов
    for (const auto& item : ds) {
        std::cout << item << "\n";
    }

    return 0;
}

