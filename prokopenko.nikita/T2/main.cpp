#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"

// Главная функция
int main() {
    std::vector<prokopenko::DataStruct> data;
    prokopenko::DataStruct temp;

    // Считываем данные до конца ввода
    while (!std::cin.eof()) {
        if (std::cin >> temp) {
            data.push_back(temp);  // Успешное чтение — добавляем в вектор
        } else {
            std::cin.clear();  // Сброс ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Пропуск до конца строки
        }
    }

    // Сортируем структуру по заданному критерию
    std::sort(data.begin(), data.end());

    // Выводим отсортированные данные
    for (const auto& el : data) {
        std::cout << el << "\n";
    }

    return 0;
}
