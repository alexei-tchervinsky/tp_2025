#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <cmath>
#include <sstream>
#include <cctype>
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
        using K1 = Key1IO;
        using Hex = HexUllIO;
        using Str = StringIO;
        in >> std::ws;
        if (in.peek() == EOF) {
            in.setstate(std::ios::failbit);
            return in;
        }
        char c;
        in.get(c);
        if (c != '(') {
            in.unget();
            in.setstate(std::ios::failbit);
            return in;
        }
        std::string field;
        bool key1_set = false, key2_set = false, key3_set = false;
        int fields_count = 0;
        while (in >> std::ws && in.peek() != ')') {
            in >> LabelIO{field} >> Delim{':'};
            if (!in) break;
            if (field == "key1") {
                in >> K1{value.key1};
                key1_set = true;
                fields_count++;
            }
            else if (field == "key2") {
                in >> Hex{value.key2};
                key2_set = true;
                fields_count++;
            }
            else if (field == "key3") {
                in >> Str{value.key3};
                key3_set = true;
                fields_count++;
            }
            else {
                in.setstate(std::ios::failbit);
                break;
            }
            if (!in) break;
            if (in.peek() == ':') {
                in >> Delim{':'};
            }
        }
        if (!key1_set || !key2_set || !key3_set || fields_count != 3) {
            in.setstate(std::ios::failbit);
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
