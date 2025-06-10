#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
#include <complex>
#include <utility>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;
};

// Перегрузки операторов
std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

bool operator<(const DataStruct& a, const DataStruct& b);

#endif // DATASTRUCT_H

