#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace nspace
{
    struct DataStruct
    {
        char key1;
        unsigned long long key2;
        std::string key3;

        friend std::istream& operator>>(std::istream&, DataStruct&);
        friend std::ostream& operator<<(std::ostream&, const DataStruct&);
    };
    bool compare(const DataStruct&, const DataStruct&);
}

#endif
