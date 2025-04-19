//
// Created by jdh99 on 15.04.2025.
//
#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

#include <iomanip>

namespace likhodievskii {
    std::ostream &operator<<(std::ostream &os, const DataStruct &ds) {
        std::ostream::sentry sentry(os);
        if (!sentry) {
            return os;
        }
        os << "(:key1 ";
        os << std::setbase(16) << ds.key1_;
        os << ":key2 #c(";
        DataStruct::printDouble(os, ds.key2_.real());
        os << " ";
        DataStruct::printDouble(os, ds.key2_.imag());
        os << "):key3 \"";
        os << ds.key3_;
        os << "\":)";
        return os;
    }

    void DataStruct::printDouble(std::ostream &out, double x) {
        iofmtguard outGuard(out);
        if (std::floor(x) == x) {
            out << std::fixed << std::setprecision(1) << x;
        } else {
            out  << x;
        }
    }


    std::istream &operator>>(std::istream &in, DataStruct &ds) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        DataStruct tmp;
        in >> DelimiterIO{'('};
        for (std::size_t i = 0; i < 3; i++) {
            short number = 0;
            in >> DelimiterIO{':' } >> DelimiterIO{ 'k' };
            in >> DelimiterIO{ 'e' } >> DelimiterIO{ 'y' } >> number;
            switch (number) {
                case HEX: {
                    in >> HexUnsignedLongLongIO{tmp.key1_ };
                    break;
                }
                case COMPLEX: {
                    in >> ComplexDoubleIO{tmp.key2_};
                    break;
                }
                case STRING: {
                    in >> StringIO{tmp.key3_};
                    break;
                }
            }
        }
        in >> DelimiterIO{':'} >> DelimiterIO{')'};
        if (in) {
            ds = tmp;
        }
        return in;
    }

    bool compare(const DataStruct &a, const DataStruct &b) {
        if (a.key1_ != b.key1_) {
            return a.key1_ < b.key1_;
        }
        double checkComplexKey1 = std::abs(a.key2_);
        double checkComplexKey2 = std::abs(b.key2_);
        if (checkComplexKey1 != checkComplexKey2) {
            return checkComplexKey1 < checkComplexKey2;
        }
        return a.key3_.length() < b.key3_.length();
    }
}
