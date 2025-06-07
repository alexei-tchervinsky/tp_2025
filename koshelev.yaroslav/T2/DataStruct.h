#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace nspace {
    struct DataStruct {
        unsigned long long key1; // ULL HEX
        double key2; // DBL SCI
        std::string key3;

        friend std::istream& operator>>(std::istream&, DataStruct&);
        friend std::ostream& operator<<(std::ostream&, const DataStruct&);
    };
    bool compare(const DataStruct&, const DataStruct&);
}

#endif
