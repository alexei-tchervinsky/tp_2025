#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <cmath>

namespace solution {
    bool DataStruct::operator<(const DataStruct& other) const {
        if (std::abs(key1 - other.key1) > 1e-6)
            return key1 < other.key1;
        if (key2 != other.key2)
            return key2 < other.key2;
        return key3 < other.key3;
    }

    std::istream& operator>>(std::istream& in, DataStruct& value) {
        using Delim = DelimiterIO;
        using Dbl = DoubleIO;
        using Hex = HexUllIO;
        using Str = StringIO;

        in >> std::ws;
        char c;
        in.get(c);
        if (c != '(') {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::string field;
        while (in >> std::ws && in.peek() != ')') {
            in >> LabelIO{field} >> Delim{':'};
            if (field == "key1") {
                in >> Dbl{value.key1};
            } else if (field == "key2") {
                in >> Hex{value.key2};
            } else if (field == "key3") {
                in >> Str{value.key3};
            } else {
                in.setstate(std::ios::failbit);
                break;
            }
            in >> Delim{':'};
        }

        in >> Delim{')'};
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& value) {
        iofmtguard guard(out);
        out << "(:key1 " << std::fixed << std::setprecision(1) << value.key1
            << ":key2 0x" << std::hex << std::uppercase << value.key2
            << std::dec << ":key3 \"" << value.key3 << "\":)";
        return out;
    }
}
