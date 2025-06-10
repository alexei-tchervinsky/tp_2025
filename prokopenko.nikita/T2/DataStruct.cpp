#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"

#include <cmath>
#include <iomanip>

namespace prokopenko {


    bool DataStruct::operator<(const DataStruct& other) const {
        double firstAbs = std::abs(key1);
        double secondAbs = std::abs(other.key1);
        if (firstAbs != secondAbs) {
            return firstAbs < secondAbs;
        }
        if (key2 != other.key2) {
            return key2 < other.key2;
        }
        return key3.size() < other.key3.size();
    }


    std::istream& operator>>(std::istream& in, DataStruct& data) {
        std::istream::sentry guard(in);
        if (!guard) {
            return in;
        }

        DataStruct temp;
        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};
        for (int i = 0; i < 3 && in; ++i) {
            std::string label;
            in >> LabelIO{label};

            if (label == "key1") {
                in >> ComplexIO{temp.key1} >> DelimiterIO{':'};
                hasKey1 = in.good();
            } else if (label == "key2") {
                in >> CharIO{temp.key2} >> DelimiterIO{':'};
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
        std::ostream::sentry guard(out);
        if (!guard) {
            return out;
        }

        iofmtguard fmtguard(out);

        out << "(:";
        out << "key1 #c(" << std::fixed << std::setprecision(1)
            << data.key1.real() << " " << data.key1.imag() << "):";
        out << "key2 '" << data.key2 << "':";
        out << "key3 " << std::quoted(data.key3) << ":)";
        return out;
    }
}
