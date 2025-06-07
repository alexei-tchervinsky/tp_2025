#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <complex>
#include <string>
#include <utility>
#include <iosfwd>

struct DataStruct {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

bool parseComplex(const std::string& str, std::complex<double>& value);
bool parseRational(const std::string& str, std::pair<long long, unsigned long long>& value);
std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
