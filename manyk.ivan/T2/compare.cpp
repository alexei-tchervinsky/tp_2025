#include "DataStruct.hpp"

bool compareData(const DataStruct& a, const DataStruct& b) {
    if (std::abs(a.key1) != std::abs(b.key1)) {
        return std::abs(a.key1) < std::abs(b.key1);
    }

    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }

    return a.key3.length() < b.key3.length();
}
