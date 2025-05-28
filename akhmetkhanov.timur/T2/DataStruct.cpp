#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>

namespace nspace {
    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        DataStruct temp{0, 0.0, {}};

        if (!(is >> DelimiterIO{ '(' })) {
            return is;
        }

        bool key1_read = false, key2_read = false, key3_read = false;

        for (std::size_t i = 0; i < 3; ++i) {
            short number = 0;

            if (!(is >> DelimiterIO{ ':' } >> LabelIO{ "key" } >> number)) {
                is.setstate(std::ios::failbit);
                return is;
            }

            switch (number) {
                case 1:
                    if (key1_read) {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    if (!(is >> ULLHexIO{ temp.key1 })) {
                        return is;
                    }
                    key1_read = true;
                    break;

                case 2:
                    if (key2_read) {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    if (!(is >> DoubleSciIO{ temp.key2 })) {
                        return is;
                    }
                    key2_read = true;
                    break;

                case 3:
                    if (key3_read) {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    if (!(is >> StringIO{ temp.key3 })) {
                        return is;
                    }
                    key3_read = true;
                    break;

                default:
                    is.setstate(std::ios::failbit);
                    return is;
            }
        }

        if (!key1_read || !key2_read || !key3_read) {
            is.setstate(std::ios::failbit);
            return is;
        }

        if (!(is >> DelimiterIO{ ':' } >> DelimiterIO{ ')' })) {
            return is;
        }

        ds = std::move(temp);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
        std::ostream::sentry sentry(os);
        if (!sentry) return os;

        iofmtguard fmtguard(os);

        os << "(:key1 0x" << std::hex << std::uppercase << ds.key1
           << ":key2 " << std::scientific << std::setprecision(1) << ds.key2
           << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }

    bool compare(const DataStruct& ds1, const DataStruct& ds2) {
        if (ds1.key1 != ds2.key1) return ds1.key1 < ds2.key1;
        if (ds1.key2 != ds2.key2) return ds1.key2 < ds2.key2;
        return ds1.key3.size() < ds2.key3.size();
    }
}
