#include "dictionary.hpp"
#include <iostream>
#include <cassert>
void test_insert_search() {
    DictionaryHashTable dict(10);
    dict.insert("apple", "яблоко");
    auto entry = dict.search("apple");
    assert(entry != nullptr);
    assert(entry->getKey() == "apple");
}
void test_remove() {
    DictionaryHashTable dict(10);
    dict.insert("car", "машина");
    assert(dict.remove("car"));
    assert(!dict.search("car"));
}
void runAllTests() {
    test_insert_search();
    test_remove();
    std::cout << "All tests passed!\n";
}
