#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>

namespace myspace {
    struct DataStruct {
        std::complex<double> key1;
        std::string key2;
        std::string key3;

        friend std::ostream& operator<<(std::ostream&, const DataStruct&);
        friend std::istream& operator>>(std::istream&, DataStruct&);
    };
    bool compare(const DataStruct&, const DataStruct&);
}

#endif

