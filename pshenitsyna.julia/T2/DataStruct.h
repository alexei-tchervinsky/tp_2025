#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H

#include <iostream>

struct DataStruct{
    unsigned long long key1;
    char key2;
    std::string key3;

    friend std::ostream& operator<<(std::ostream&, const DataStruct&);
    friend std::istream& operator>>(std::istream&, DataStruct&);
};

#endif //T2_DATASTRUCT_H
