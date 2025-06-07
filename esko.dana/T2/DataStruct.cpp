#include "DataStruct.h"
#include "iofmtguard.h"
#include "IO_Objects.h"
#include <algorithm>
#include <iomanip>

namespace Data {
    std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
        std::ostream::sentry sentry(os);
        if (!sentry) {
            return os;
        }
        os << "(:key1 " << ds.key1 << "sll";
        os << ":key2 " << std::fixed << ds.key2 << "d";
        os << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }

    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        DataStruct temp;
        is >> LimitingSymbolIO{ '(' };
        for (std::size_t i = 0; i < 3; ++i) {
            short number;
            is >> LimitingSymbolIO{ ':' } >> LabelIO{ "key" } >> number;
            switch (number) {
                case 1: {
                    is >> SignedLongLongIO{ temp.key1 };
                    break;
                }
                case 2: {
                    is >> DoubleIO{ temp.key2 };
                    break;
                }
                case 3: {
                    is >> StringIO{ temp.key3 };
                    break;
                }
            }
        }
        is >> LimitingSymbolIO{ ':' } >> LimitingSymbolIO{ ')' };
        if (is) {
            ds = temp;
        }
        return is;
    }

    bool compareDataStruct(const DataStruct& ds1, const DataStruct& ds2) {
        if (ds1.key1 != ds2.key1) {
            return ds1.key1 < ds2.key1;
        }
        if (ds1.key2 != ds2.key2) {
            return ds1.key2 < ds2.key2;
        }
        return ds1.key3.length() < ds2.key3.length();
    }
}
