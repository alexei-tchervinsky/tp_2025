#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include <iomanip>
#include <sstream>
#include "iofmtguard.hpp"

namespace solution {
    bool DataStruct::operator<(const DataStruct& other) const {
        if (key1 != other.key1) {
            return key1 < other.key1;
        }
        if (key2 != other.key2) {
            return key2 < other.key2;
        }
        return key3.size() < other.key3.size();
    }

    std::istream& operator>>(std::istream& in, DataStruct& value) {
        using Delim = DelimiterIO;
        using Dbl = DoubleIO;
        using Hex = HexUllIO;
        using Str = StringIO;

        in >> Delim{'('} >> Dbl{value.key1} >> Delim{';'};
        in >> Hex{value.key2} >> Delim{';'};
        in >> Str{value.key3} >> Delim{':'} >> Delim{')'};
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& value) {
        iofmtguard guard(out);
        out << "(" << std::fixed << std::setprecision(1) << value.key1 << ";";
        out << std::hex << std::uppercase << "0x" << value.key2 << ";";
        out << std::dec << "\"" << value.key3 << "\"" << ":)";
        return out;
    }
}
