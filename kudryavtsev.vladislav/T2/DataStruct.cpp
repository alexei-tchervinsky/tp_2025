#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

#include <algorithm>
#include <iomanip>

namespace myspace {
    std::ostream& operator<<(std::ostream &os, const DataStruct& ds) {
        std::ostream::sentry sentry(os);
        if(!sentry) return os;
        iofmtguard fmtguard(os);
        os << ":key1 #c(" << ds.key1.real() << ' ' << ds.key1.imag() << ")\n";
        os << ":key2 " << ds.key2 << ":\n";
        os << ":key3 \"" << ds.key3 << "\":";
        return os;
    }

    std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        DataStruct temp;
        is >> LimitingSymbolIO{'('};
        for(std::size_t i = 0; i < 3; ++i) {
            short number;
            is >> LimitingSymbolIO{':'} >> LabelIO{"key"} >> number;
            switch(number){
                case 1: {
                    is >> ComplexIO{temp.key1};
                    break;
                }
                case 2: {
                    is >> BinaryIO{temp.key2};
                    break;
                }
                case 3: {
                    is >> StringIO{temp.key3};
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

    bool compare(const DataStruct& ds1, const DataStruct& ds2) {
        if(ds1.key1 == ds2.key1){
            unsigned long long num1;
            unsigned long long num2;
            long long size1 = ds1.key2.size() - 3;
            long long size2 = ds2.key2.size() - 3;
            while(size1 >= 0){
                num1 += ds1.key2[size1] * pow(2, size1);
                --size1;
            }
            while(size2 >= 0){
                num2 += ds2.key2[size1] * pow(2, size2);
                --size2;
            }
            return num1 < num2;
        }
        else if(ds1.key1 == ds2.key1 and ds1.key2 == ds2.key2) return ds1.key3.size() < ds2.key3.size();
        else return abs(ds1.key1) < abs(ds2.key1);
    }
}