#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

namespace solution {

    struct DataStruct {
        double key1;
        unsigned long long key2;
        std::string key3;
    };

    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);

} // namespace solution

#endif // DATASTRUCT_HPP
