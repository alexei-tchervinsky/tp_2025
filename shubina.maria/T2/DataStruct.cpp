#include "DataStruct.h"
#include <cmath>

DataStruct::DataStruct() : key1('\0'), key2(0), key3("") {}

bool DataStruct::operator<(const DataStruct& other) const {
    if (key1 != other.key1)
        return key1 < other.key1;
    if (key2 != other.key2)
        return key2 < other.key2;
    return key3.size() < other.key3.size();
}

