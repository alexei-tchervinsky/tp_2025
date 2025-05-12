#include "DataStruct.h"
#include "iofmtguard.h"
#include "ObjectsIO.h"

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::string keyLabel;
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
        in >> sep{'('};
        in >> sep{':'};
        bool isKey1 = false, isKey2 = false, isKey3 = false;
        while(in.peek() != ')')
        {
            if(!(in >> keyLabel))
            {
                break;
            }
            if (keyLabel == "key1" && !isKey1)
            {
                in >> sep{' '} >> oct{input.key1} >> sep{':'};
                isKey1 = true;
            }
            else if (keyLabel == "key2" && !isKey2)
            {
                in >> sep{' '} >> chr{input.key2} >> sep{':'};
                isKey2 = true;
            }
            else if (keyLabel == "key3" && !isKey3)
            {
                in >> sep{' '} >> str{input.key3} >> sep{':'};
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
        in >> sep{')'};
        dest = input;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& src)

{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << '0' <<src.key1 << ":";
    out << "key2 " << '\'' << src.key2 << '\'' << ":";
    out << "key3 " << '"' << src.key3 << '"' << ":)";
    return out;
}
