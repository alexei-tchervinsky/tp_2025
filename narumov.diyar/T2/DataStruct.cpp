#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

#include <algorithm>
#include <iomanip>

namespace narumov {
    std::ostream& operator<<(std::ostream &os, const DataStruct& ds) {
        std::ostream::sentry sentry(os);
        if(!sentry) {
            return os;
        }
        auto printDotted = [&](double x) {
            iofmtguard fmtguard(os);
            if(std::floor(x) == x) {
                os << std::fixed << std::setprecision(1) << x;
            } else {
                os << x;
            }
        };
        os << "(:key1 #c(";
        printDotted(ds.key1.real());
        os << ' ';
        printDotted(ds.key1.imag());
        os << ')';
        os << ":key2 (:N " << ds.key2.first << ":D " << ds.key2.second << ":)";
        os << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }

    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        DataStruct temp;
        is >> LimitingSymbolIO { '(' };
        for(std::size_t i = 0; i < 3; ++i) {
            short number;
            is >> LimitingSymbolIO { ':' } >> LabelIO { "key" } >> number;
            switch(number) {
                case 1: {
                    is >> ComplexIO { temp.key1 };
                    break;
                }
                case 2: {
                    is >> RationalIO { temp.key2 };
                    break;
                }
                case 3: {
                    is >> StringIO { temp.key3 };
                    break;
                }
            }
        }
        is >> LimitingSymbolIO { ':' } >> LimitingSymbolIO { ')' };
        if(is) {
            ds = temp;
        }
        return is;
    }

    bool compareDataStruct(const DataStruct& ds1, const DataStruct& ds2) {
        double m1 = std::abs(ds1.key1);
        double m2 = std::abs(ds2.key1);
        if(m1 != m2) {
            return m1 < m2;
        }
        unsigned long long lcm = (ds1.key2.second * ds2.key2.second) / std::__gcd(ds1.key2.second, ds2.key2.second);
        long long v1 = ds1.key2.first * (lcm / ds1.key2.second);
        long long v2 = ds2.key2.first * (lcm / ds2.key2.second);
        if(v1 != v2) {
            return v1 < v2;
        }
        return ds1.key3.length() < ds2.key3.length();
    }
}
