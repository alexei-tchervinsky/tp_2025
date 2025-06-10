#pragma once

#include <string>
#include <ostream>
#include <istream>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
};

