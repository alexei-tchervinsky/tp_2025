#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <iostream>

namespace ryzhov {
struct DelimiterIO {
        char delimiter;
};

struct ComplexDoubleIO {
        std::complex<double> &ref;
};

struct StringIO {
        std::string &ref;
};

struct SignedLongLongIO {
        long long &ref;
};

struct LabelIO {
        std::string label;
};

std::istream &operator>>(std::istream &, LabelIO &&);
std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, ComplexDoubleIO &&dest);
std::istream &operator>>(std::istream &in, SignedLongLongIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
} // namespace ryzhov

#endif // IO_OBJECTS_HPP
