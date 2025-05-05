#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "IO_Objects.hpp"

namespace tarasov {
    bool DataStruct::operator<(const DataStruct& other) const {
        if (key1 != other.key1) {
            return key1 < other.key1;
        }
        if (key2 != other.key2) {
            return key2 < other.key2;
        }
        return key3.length() < other.key3.length();
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        DataStruct data;
        std::string key_label;
        bool key1_read = false, key2_read = false, key3_read = false;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};
        if (!in) return in;

        while (in.peek() != ')') {
            if (!(in >> key_label)) break;

            if (key_label == "key1") {
                if (!(in >> DoubleSciIO{data.key1} >> DelimiterIO{':'}) or data.key1 == 0) break;
                key1_read = true;
            } else if (key_label == "key2") {
                if (!(in >> CharLitIO{data.key2} >> DelimiterIO{':'})) break;
                key2_read = true;
            } else if (key_label == "key3") {
                if (!(in >> StringLitIO{data.key3} >> DelimiterIO{':'})) break;
                key3_read = true;
            } else {
                std::string dummy;
                std::getline(in, dummy, ':');
                if (!in) break;
            }

            if (in.peek() == ')') break;
            in >> std::ws;
        }

        in >> DelimiterIO{')'};

        if (in && key1_read && key2_read && key3_read) {
            dest = data;
        } else {
            in.setstate(std::ios::failbit);

            /*
            if (in.fail()) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            */
        }
        return in;
    }

    std::string formatScientific(const double data) {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(2) << data;
        std::string str = oss.str();

        size_t e_pos = str.find('e');
        if (e_pos != std::string::npos) {
            if (str[e_pos + 2] == '0') {
                str.erase(e_pos + 2, 1);
            }
        }
        return str;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        const std::ostream::sentry sentry(out);
        if (!sentry) return out;

        iofmtguard fmtguard(out);

        out << "(:";
        out << "key1 " << formatScientific(data.key1) << ":";
        out << "key2 " << '\'' << data.key2 << '\'' << ":";
        out << "key3 " << std::quoted(data.key3);
        out << ":)";

        return out;
    }
}
