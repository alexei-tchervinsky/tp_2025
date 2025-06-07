#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>

namespace myspace {
    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        DataStruct temp{0, 0.0, {}};
        is >> DelimiterIO{ '(' };
        if (!is) return is;

        for (std::size_t i = 0; i < 3; ++i) {
            short number = 0;
            is >> DelimiterIO{ ':' } >> LabelIO{ "key" } >> number;
            if (is.fail()) return is;

            switch (number) {
                case 1: is >> ULLHexIO{ temp.key1 }; break;
                case 2: is >> DoubleSciIO{ temp.key2 }; break;
                case 3: is >> StringIO{ temp.key3 }; break;
                default: is.setstate(std::ios::failbit);
            }
            if (!is) return is;
        }

        is >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        if (is) ds = std::move(temp);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
        std::ostream::sentry sentry(os);
        if (!sentry) return os;

        iofmtguard fmtguard(os);
        os << "(:key1 0x" << std::hex << std::uppercase << ds.key1 << std::dec
           << ":key2 " << std::scientific << ds.key2
           << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }

    bool compare(const DataStruct& ds1, const DataStruct& ds2) {
        if (ds1.key1 != ds2.key1) return ds1.key1 < ds2.key1;
        if (ds1.key2 != ds2.key2) return ds1.key2 < ds2.key2;
        return ds1.key3.size() < ds2.key3.size();
    }
}
