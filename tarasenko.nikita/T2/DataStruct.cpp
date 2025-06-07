#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

#include <iomanip>

namespace tarsenko {
    std::ostream& operator<<(std::ostream& out, const DataStruct& src)

    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << '0' << src.key1 << ":";
        out << "key2 " << '\'' << src.key2 << '\'' << ":";
        out << "key3 " << '"' << src.key3 << '"' << ":)";
        return out;
    }


    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        using sep = DelimiterIO;
        using oct = OctIO;
        using chr = CharIO;
        using str = StringIO;
        in >> sep{ '(' } >> sep{ ':' };
        bool isKey1 = false, isKey2 = false, isKey3 = false;
        while (in.peek() != ')')
        {
            std::string keyLabel;
            if (!(in >> keyLabel))
            {
                break;
            }
            if (keyLabel == "key1" && !isKey1)
            {
                in >> oct{ input.key1 } >> sep{ ':' };
                isKey1 = true;

            }
            else if (keyLabel == "key2" && !isKey2)
            {
                in >> chr{ input.key2 } >> sep{ ':' };
                isKey2 = true;

            }
            else if (keyLabel == "key3" && !isKey3)
            {
                in >> str{ input.key3 } >> sep{ ':' };
                isKey3 = true;

            }
            else
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }
        if (in && isKey1 && isKey2 && isKey3)
        {
            in >> sep{ ')' };
            dest = input;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    bool DataStructSort(const DataStruct& dest1, const DataStruct& dest2)
    {
        if (dest1.key1 != dest2.key1)
        {
            return dest1.key1 < dest2.key1;
        }
        if (dest1.key2 != dest2.key2)
        {
            return dest1.key2 < dest2.key2;
        }
        return dest1.key3.length() < dest2.key3.length();
    }
}
