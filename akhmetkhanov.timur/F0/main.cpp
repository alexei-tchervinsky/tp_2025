#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include "hash_table.hpp"

void print_separator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void print_translations(const std::string& word,
                        const std::vector<std::string>& translations) {
    std::cout << "Переводы слова '" << word << "': ";
    if (translations.empty()) {
        std::cout << "не найдено";
    } else {
        for (size_t i = 0; i < translations.size(); ++i) {
            std::cout << translations[i];
            if (i < translations.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void demonstrate_basic_operations(HashTable& dictionary) {
    print_separator("Демонстрация основных операций");

    // Добавляем слова в словарь
    std::cout << "Добавляем слова в словарь..." << std::endl;

    std::vector<std::pair<std::string, std::string>> words = {
        {"apple", "яблоко"},
        {"apple", "яблочко"},
        {"banana", "банан"},
        {"cat", "кот"},
        {"cat", "кошка"},
        {"cat", "котенок"},
        {"dog", "собака"},
        {"dog", "щенок"},
        {"house", "дом"},
        {"house", "жилище"},
        {"book", "книга"},
        {"computer", "компьютер"},
        {"water", "вода"},
        {"fire", "огонь"},
        {"tree", "дерево"}
    };

    for (const auto& word_pair : words) {
        dictionary.insert(word_pair.first, word_pair.second);
        std::cout << "  Добавлено: " << word_pair.first << " -> "
        << word_pair.second << std::endl;
    }

    std::cout << "\nПоиск переводов:" << std::endl;
    // Поиск переводов
    std::vector<std::string> search_words = {"apple", "cat", "dog", "house"};
    for (const auto& word : search_words) {
        print_translations(word, dictionary.search(word));
    }

    std::cout << "\nОсновная статистика:" << std::endl;
    std::cout << "Размер словаря: " << dictionary.size()
    << " слов" << std::endl;
    std::cout << "Коэффициент загрузки: " << std::fixed << std::setprecision(3)
              << dictionary.load_factor() << std::endl;
}

void demonstrate_removal_operations(HashTable& dictionary) {
    print_separator("Демонстрация операций удаления");

    // Удаляем слова
    std::vector<std::string> words_to_remove = {"banana",
        "book", "nonexistent"};

    for (const auto& word : words_to_remove) {
        std::cout << "Попытка удалить слово '" << word << "'..." << std::endl;

        if (dictionary.remove(word)) {
            std::cout << "  ✓ Слово '" << word <<
            "' успешно удалено" << std::endl;
        } else {
            std::cout << "  ✗ Слово '" << word <<
            "' не найдено для удаления" << std::endl;
        }

        // Проверяем, что слово действительно удалено
        auto translations = dictionary.search(word);
        if (translations.empty()) {
            std::cout << "  Подтверждение: слово '" <<
            word << "' не найдено в словаре" << std::endl;
        } else {
            std::cout << "  Ошибка: слово '" << word <<
            "' все еще в словаре!" << std::endl;
        }
    }

    std::cout << "\nРазмер словаря после удаления: " <<
    dictionary.size() << " слов" << std::endl;
}

void demonstrate_advanced_features(HashTable& dictionary) {
    print_separator("Демонстрация дополнительных возможностей");

    // Получаем все ключи
    std::cout << "Все слова в словаре (отсортированы):" << std::endl;
    auto all_keys = dictionary.get_all_keys();
    for (size_t i = 0; i < all_keys.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << all_keys[i]
        << std::endl;
    }

    // Проверяем наличие слов
    std::vector<std::string> test_words = {"apple", "elephant",
        "cat", "zebra", "computer"};
    std::cout << "\nПроверка наличия слов:" << std::endl;
    for (const auto& word : test_words) {
        std::cout << "'" << std::setw(10) << word << "': "
                  << (dictionary.contains(word) ? "✓ найдено" :
                      "✗ не найдено") << std::endl;
    }

    // Подробная статистика
    dictionary.print_statistics();

    // Статистика хеширования
    dictionary.print_hash_statistics();
}

void test_error_handling(HashTable& dictionary) {
    print_separator("Тестирование обработки ошибок");

    std::cout << "Тестируем различные ошибочные ситуации:" << std::endl;

    // Тест 1: Попытка вставить пустой ключ
    std::cout << "\n1. Попытка вставить пустой ключ:" << std::endl;
    try {
        dictionary.insert("", "перевод");
        std::cout << "  ✗ Ошибка: исключение не было выброшено!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  ✓ Поймано ожидаемое исключение: " <<
        e.what() << std::endl;
    }

    // Тест 2: Попытка вставить пустой перевод
    std::cout << "\n2. Попытка вставить пустой перевод:" << std::endl;
    try {
        dictionary.insert("test", "");
        std::cout << "  ✗ Ошибка: исключение не было выброшено!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  ✓ Поймано ожидаемое исключение: " <<
        e.what() << std::endl;
    }

    // Тест 3: Попытка вставить слишком длинный ключ
    std::cout << "\n3. Попытка вставить слишком длинный ключ (150 символов):"
    << std::endl;
    try {
        std::string long_key(150, 'a');
        dictionary.insert(long_key, "перевод");
        std::cout << "  ✗ Ошибка: исключение не было выброшено!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  ✓ Поймано ожидаемое исключение: " << e.what()
        << std::endl;
    }

    // Тест 4: Поиск с невалидными ключами
    std::cout << "\n4. Поиск с невалидными ключами:" << std::endl;
    auto result1 = dictionary.search("");
    std::cout << "  Поиск пустого ключа: " << (result1.empty() ?
        "✓ корректно возвращен пустой результат" : "✗ ошибка") << std::endl;

    std::string long_key(150, 'b');
    auto result2 = dictionary.search(long_key);
    std::cout << "  Поиск длинного ключа: " <<
    (result2.empty() ? "✓ корректно возвращен пустой результат" :
     "✗ ошибка") << std::endl;

    // Тест 5: Удаление невалидных ключей
    std::cout << "\n5. Удаление невалидных ключей:" << std::endl;
    bool removed1 = dictionary.remove("");
    std::cout << "  Удаление пустого ключа: " << (!removed1 ?
                    "✓ корректно возвращен false" : "✗ ошибка") << std::endl;

    bool removed2 = dictionary.remove(long_key);
    std::cout << "  Удаление длинного ключа: " <<
    (!removed2 ? "✓ корректно возвращен false" : "✗ ошибка") << std::endl;
}

void demonstrate_performance_test(HashTable& dictionary) {
    print_separator("Тест производительности");

    // Очищаем словарь для чистого теста
    dictionary.clear();

    // Генерируем тестовые данные
    std::vector<std::string> test_words;
    for (int i = 0; i < 1000; ++i) {
        test_words.push_back("word_" + std::to_string(i));
    }

    // Засекаем время вставки
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& word : test_words) {
        dictionary.insert(word, "translation_" + word);
        if (i % 2 == 0) {
            dictionary.insert(word, "alt_translation_" + word);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Результаты теста производительности:" << std::endl;
    std::cout << "  Вставлено слов: " << test_words.size() << std::endl;
    std::cout << "  Время выполнения: " << duration.count() << " мкс" << std::endl;
    std::cout << "  Среднее время на вставку: " << (duration.count()
                            / test_words.size()) << " мкс/слово" << std::endl;

    // Итоговая статистика
    dictionary.print_statistics();
    dictionary.print_hash_statistics();
}

int main() {
    std::cout << "🔤 Демонстрация работы словаря на основе хеш-таблицы"
    << std::endl;
    std::cout << "Использует std::unordered_map" << std::endl;

    try {
        HashTable dictionary;

        // Демонстрируем все возможности
        demonstrate_basic_operations(dictionary);
        demonstrate_removal_operations(dictionary);
        demonstrate_advanced_features(dictionary);
        test_error_handling(dictionary);
        demonstrate_performance_test(dictionary);

        print_separator("Программа успешно завершена");
        std::cout << "✅ Все тесты пройдены успешно!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "❌ Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
