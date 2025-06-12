#include "DataStruct.h"
#include "IO_Objects.h"
#include "iofmtguard.h"
#include <iomanip>
#include <sstream>
#include <cctype>

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

    std::istream& operator>>(std::istream& in, DataStruct& data) {
        std::istream::sentry guard(in);
        if (!guard) return in;

        DataStruct temp;
        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};
        for (int i = 0; i < 3 && in; ++i) {
            std::string label;
            in >> LabelIO{label};

            if (label == "key1") {
                in >> DoubleSciIO{temp.key1} >> DelimiterIO{':'};
                hasKey1 = in.good();
            } else if (label == "key2") {
                in >> ULLHexIO{temp.key2} >> DelimiterIO{':'};
                hasKey2 = in.good();
            } else if (label == "key3") {
                in >> StringIO{temp.key3} >> DelimiterIO{':'};
                hasKey3 = in.good();
            } else {
                std::string skip;
                std::getline(in, skip, ':');
            }
        }

        in >> DelimiterIO{')'};
        if (hasKey1 && hasKey2 && hasKey3) {
            data = temp;
        } else {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        iofmtguard fmt(out);
        out << "(:";
        out << "key1 " << std::scientific << std::uppercase << std::setprecision(6) << data.key1 << ":";
        out << "key2 0X" << std::uppercase << std::hex << data.key2 << ":";
        out << "key3 " << std::quoted(data.key3) << ":)";
        return out;
    }

}
