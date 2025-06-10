#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <ostream>
#include <istream>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;

    DataStruct();
    bool operator<(const DataStruct& other) const;
};

#endif // DATASTRUCT_H

