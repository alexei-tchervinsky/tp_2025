#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace nspace {
    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        DataStruct temp{0, 0.0, {}};
        is >> DelimiterIO{ '(' };
        if (!is) return is;

        bool hasValidKeys = false;
        for (std::size_t i = 0; i < 3; ++i) {
            short number = 0;
            is >> DelimiterIO{ ':' } >> LabelIO{ "key" } >> number;
            if (is.fail()) {
                is.clear();
                break;
            }

            std::streampos pos = is.tellg();
            bool keyValid = true;

            switch (number) {
                case 1:
                    if (!(is >> ULLHexIO{ temp.key1 })) keyValid = false;
                    break;
                case 2:
                    if (!(is >> DoubleSciIO{ temp.key2 })) {
                        is.clear();
                        is.seekg(pos);
                        if (!(is >> temp.key2)) keyValid = false;
                    }
                    break;
                case 3:
                    if (!(is >> StringIO{ temp.key3 })) keyValid = false;
                    break;
                default:
                    keyValid = false;
            }

            if (!keyValid) {
                is.clear();
                is.seekg(pos);
                break;
            }

            hasValidKeys = true;
        }

        if (hasValidKeys) {
            char c;
            while (is >> c && c != ')') {}
            if (is) ds = std::move(temp);
        } else {
            is.setstate(std::ios::failbit);
        }

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
