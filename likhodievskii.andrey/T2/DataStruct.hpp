//
// Created by jdh99 on 15.04.2025.
//

#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>

namespace likhodievskii {
    enum key_number { HEX = 1, COMPLEX = 2, STRING = 3 };

    struct DataStruct {
        unsigned long long key1_;
        std::complex<double> key2_;

        std::string key3_;

        friend std::ostream &operator<<(std::ostream &out, const DataStruct &src);

        friend std::istream &operator>>(std::istream &in, DataStruct &dest);

    private:
        static void printDouble(std::ostream &out, double x);
    };

    bool compare(const DataStruct &a, const DataStruct &b);
}

#endif //DATASTRUCT_HPP
