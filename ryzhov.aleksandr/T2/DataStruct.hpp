#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>

namespace ryzhov {
enum key_number { CMP = 1, SLL = 2, STR = 3 };

struct DataStruct {
        std::complex<double> key1_;
        signed long long key2_;
        std::string key3_;
        friend std::ostream &operator<<(std::ostream &out,
                                        const DataStruct &src);
        friend std::istream &operator>>(std::istream &in, DataStruct &dest);

    private:
        static void printDouble(std::ostream &out, double x);
};

bool compare(const DataStruct &a, const DataStruct &b);
} // namespace ryzhov

#endif // DATASTRUCT_HPP
