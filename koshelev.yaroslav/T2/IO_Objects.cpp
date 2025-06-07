#include "IO_Objects.h"
#include "DataStruct.h"
#include <iostream>
#include <string>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string value;
    in >> value;
    if (!parseComplex(value, data.key1)) {
        in.setstate(std::ios::failbit);
    }
    in >> value;
    if (!parseRational(value, data.key2)) {
        in.setstate(std::ios::failbit);
    }
    in >> data.key3;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "#c(" << data.key1.real() << " " << data.key1.imag() << ")"
        << " :key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)"
        << " " << data.key3;
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    double ratA = static_cast<double>(a.key2.first) / a.key2.second;
    double ratB = static_cast<double>(b.key2.first) / b.key2.second;
    if (std::abs(ratA - ratB) > 1e-6) {
        return ratA < ratB;
    }
    if (std::abs(a.key1.imag() - b.key1.imag()) > 1e-6) {
        return a.key1.imag() < b.key1.imag();
    }
    return a.key3.length() < b.key3.length();
}
