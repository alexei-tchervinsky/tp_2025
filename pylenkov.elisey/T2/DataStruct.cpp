#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

namespace nspace
{
    std::istream& operator>>(std::istream& is, DataStruct& ds)
    {
        std::istream::sentry sentry(is);
        if(!sentry)
        {
            return is;
        }
        DataStruct temp;
        is >> DelimiterIO { '(' };
        for(std::size_t i = 0; i < 3; ++i)
        {
            short number;
            is >> DelimiterIO { ':' } >> LabelIO { "key" } >> number;
            switch(number)
            {
                case 1:
                {
                    is >> CharIO { temp.key1 };
                    break;
                }
                case 2:
                {
                    is >> ULLHexIO { temp.key2 };
                    break;
                }
                case 3:
                {
                    if (!(is >> StringIO { temp.key3 }))
                    {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    break;
                }
                default:
                    is.setstate(std::ios::failbit);
                    return is;
            }
        }
        is >> DelimiterIO { ':' } >> DelimiterIO { ')' };
        if(is)
        {
            ds = temp;
        }
        return is;
    }


    std::ostream& operator<<(std::ostream &os, const DataStruct &ds)
    {
        std::ostream::sentry sentry(os);
        if (!sentry)
        {
            return os;
        }
        iofmtguard fmtguard(os);
        os << "(:key1 '" << ds.key1 << "':key2 0x" << std::hex\
        << std::uppercase << ds.key2 << std::dec <<":key3 \"" << ds.key3 << "\":)";

        return os;
    }

    bool compare(const DataStruct &ds1, const DataStruct &ds2)
    {
        if (ds1.key1 != ds2.key1) return ds1.key1 < ds2.key1;
        if (ds1.key2 != ds2.key2) return ds1.key2 < ds2.key2;
        return ds1.key3.size() < ds2.key3.size();
    }
}
