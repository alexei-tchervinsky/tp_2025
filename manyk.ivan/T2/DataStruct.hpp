#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <string>
#include <sstream>
#include <iterator>
#include <cctype>
#include <iomanip>

struct DataStruct {
    std::complex<double> key1; // CMP LSP
    unsigned long long key2;   // ULL OCT
    std::string key3;

    friend std::istream& operator>>(std::istream& in, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& out, const DataStruct& data);
};

bool compareData(const DataStruct& a, const DataStruct& b);

#endif
