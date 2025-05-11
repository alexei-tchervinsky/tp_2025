#include "DataStruct.h"
#include "iofmtguard.h"
#include "ObjectsIO.h"

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    DataStruct input;
    {
        using sep = DelimiterIO;
        using label = LabelIO;
        using oct = OctIO;
        using chr = CharIO;
        using str = StringIO;
        in >> sep{'('};
        in >> sep{':'};
        in >> label{"key1"} >> sep{' '} >> oct{input.key1};
        in >> sep{':'};
        in >> label{"key2"} >> sep{' '} >> chr{input.key2};
        in >> sep{':'};
        in >> label{"key3"} >> sep{' '} >> str{input.key3};
        in >> sep{':'};
        in >> sep{')'};
    }
    if (in)
    {
        dest = input;
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
    out << "(:key1 " << src.key1 << ":";
    out << "key2 " << src.key2 << ":";
    out << "key3 " << src.key2 << ":)";
    return out;
}
