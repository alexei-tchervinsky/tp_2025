//
// Created by jdh99 on 17.04.2025.
//

#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <iostream>

namespace likhodievskii {
    struct DelimiterIO {
        char delimiter;
    };

    struct LabelIO {
        std::string label;
    };

    struct ComplexDoubleIO {
        std::complex<double> &ref;
    };

    struct StringIO {
        std::string &ref;
    };

    struct HexUnsignedLongLongIO {
        unsigned long long &ref;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);

    std::istream &operator>>(std::istream &in, LabelIO &&dest);

    std::istream &operator>>(std::istream &in, ComplexDoubleIO &&dest);

    std::istream &operator>>(std::istream &in, HexUnsignedLongLongIO &&dest);

    std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif //IO_OBJECTS_HPP
