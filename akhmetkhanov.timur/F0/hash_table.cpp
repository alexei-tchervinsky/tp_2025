#include "hash_table.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

bool HashTable::is_valid_key(const std::string& key) const {
    return !key.empty() && key.length() <= 100;
}

void HashTable::insert(const std::string& key, const std::string& translation) {
    if (!is_valid_key(key)) {
        throw std::invalid_argument("Invalid key");
    }

    if (translation.empty()) {
        throw std::invalid_argument("Translation cannot be empty");
    }

    auto& translations = dictionary[key];

    auto it = std::find(translations.begin(), translations.end(), translation);
    if (it == translations.end()) {
        translations.push_back(translation);
        std::sort(translations.begin(), translations.end());
    }
}

std::vector<std::string> HashTable::search(const std::string& key) const {
    if (!is_valid_key(key)) {
        return {};
    }

    auto it = dictionary.find(key);
    if (it != dictionary.end()) {
        return it->second;
    }
    return {};
}

bool HashTable::remove(const std::string& key) {
    if (!is_valid_key(key)) {
        return false;
    }

    auto it = dictionary.find(key);
    if (it != dictionary.end()) {
        dictionary.erase(it);
        return true;
    }
    return false;
}

std::vector<std::string> HashTable::get_all_keys() const {
    std::vector<std::string> keys;
    keys.reserve(dictionary.size());

    for (const auto& pair : dictionary) {
        keys.push_back(pair.first);
    }

    std::sort(keys.begin(), keys.end());
    return keys;
}

bool HashTable::contains(const std::string& key) const {
    return dictionary.find(key) != dictionary.end();
}

void HashTable::print_statistics() const {
    std::cout << "=== Статистика словаря ===" << std::endl;
    std::cout << "Количество слов: " << size() << std::endl;
    std::cout << "Коэффициент загрузки: " << std::fixed << std::setprecision(3)
              << load_factor() << std::endl;
    std::cout << "Количество корзин: " << dictionary.bucket_count() << std::endl;

    if (!empty()) {
        size_t total_translations = 0;
        size_t max_translations = 0;

        for (const auto& pair : dictionary) {
            total_translations += pair.second.size();
            max_translations = std::max(max_translations, pair.second.size());
        }

        double avg_translations = static_cast<double>(total_translations)
        / size();
        std::cout << "Среднее количество переводов на слово: "
                  << std::fixed << std::setprecision(2) << avg_translations
        << std::endl;
        std::cout << "Максимальное количество переводов для одного слова: "
                  << max_translations << std::endl;
    }
}

void HashTable::print_hash_statistics() const {
    std::cout << "\n=== Статистика хеширования ===" << std::endl;
    std::cout << "Используется кастомная хеш-функция на основе std::hash"
    << std::endl;
    std::cout << "Количество корзин: " << dictionary.bucket_count()
    << std::endl;
    std::cout << "Коэффициент загрузки: " << std::fixed << std::setprecision(3)
              << load_factor() << std::endl;
    std::cout << "Максимальный коэффициент загрузки: "
              << std::fixed << std::setprecision(3) <<
    dictionary.max_load_factor() << std::endl;

    if (!empty()) {
        // Показываем распределение по корзинам
        std::vector<size_t> bucket_sizes;
        size_t max_bucket_size = 0;
        size_t empty_buckets = 0;

        for (size_t i = 0; i < dictionary.bucket_count(); ++i) {
            size_t bucket_size = dictionary.bucket_size(i);
            bucket_sizes.push_back(bucket_size);
            max_bucket_size = std::max(max_bucket_size, bucket_size);
            if (bucket_size == 0) {
                empty_buckets++;
            }
        }

        std::cout << "Максимальный размер корзины: " <<
        max_bucket_size << std::endl;
        std::cout << "Пустых корзин: " << empty_buckets << " из "
                  << dictionary.bucket_count() << std::endl;

        // Показываем примеры хеш-значений
        std::cout << "\nПримеры хеш-значений:" << std::endl;
        int count = 0;
        for (const auto& pair : dictionary) {
            if (count++ >= 5) break; // Показываем только первые 5
            std::cout << "'" << pair.first << "' -> hash: "
            << get_hash_value(pair.first)
                      << " -> bucket: " << dictionary.bucket(pair.first)
            << std::endl;
        }
    }
}

std::size_t HashTable::get_hash_value(const std::string& key) const {
    CustomStringHash hasher;
    return hasher(key);
}
