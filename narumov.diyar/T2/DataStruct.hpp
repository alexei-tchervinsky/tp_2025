#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>

namespace narumov {
    struct DataStruct {
        std::complex<double> key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;

        friend std::ostream& operator<<(std::ostream&, const DataStruct&);
        friend std::istream& operator>>(std::istream&, DataStruct&);
    };

    bool compareDataStruct(const DataStruct&, const DataStruct&);
}

#endif
