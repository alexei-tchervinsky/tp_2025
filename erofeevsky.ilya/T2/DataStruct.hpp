#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <utility>

namespace erofick{
    struct DataStruct
    {
        long long key1;
        char key2;
        std::string key3;

        friend std::ostream& operator<<(std::ostream&, const DataStruct&);
        friend std::istream& operator>>(std::istream&, DataStruct&);
    };

    bool compareDataStruct(const DataStruct&, const DataStruct&);
}

#endif
