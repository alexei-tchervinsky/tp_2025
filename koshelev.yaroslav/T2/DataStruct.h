#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <complex>
#include <utility>
#include <iostream>

namespace solution {
    struct DataStruct {
        std::complex<double> key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
