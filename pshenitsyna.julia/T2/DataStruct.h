#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H

#include <iostream>

struct DataStruct{
    unsigned long long key1;
    char key2;
    std::string key3;

    friend std::ostream& operator<<(std::ostream&, const DataStruct& src);
    friend std::istream& operator>>(std::istream&, DataStruct& dest);
};

#endif //T2_DATASTRUCT_H
