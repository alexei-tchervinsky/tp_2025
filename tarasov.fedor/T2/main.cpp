#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <limits>

namespace nspace {
    struct DataStruct {
        double key1;
        char key2;
        std::string key3;

        bool operator<(const DataStruct& other) const {
            if (key1 != other.key1) {
                return key1 < other.key1;
            }
            if (key2 != other.key2) {
                return key2 < other.key2;
            }
            return key3.length() < other.key3.length();
        }
    };

    struct DelimiterIO {
        char exp;
    };

    struct LabelIO {
        std::string exp;
    };

    struct DoubleSciIO {
        double& ref;
    };

    struct CharLitIO {
        char& ref;
    };

    struct StringLitIO {
        std::string& ref;
    };

    char readChar(std::istream& in) {
        char c = 0;
        in >> c;
        return c;
    }

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& s) :
            s_(s),
            fill_(s.fill()),
            precision_(s.precision()),
            fmt_(s.flags()) {}
        ~iofmtguard() {
            s_.fill(fill_);
            s_.precision(precision_);
            s_.flags(fmt_);
        }
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        char c = 0;
        in >> std::ws;
        if (!in) return in;

        in >> c;

        if (in && c != dest.exp) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        std::string read_str;
        char c;

        while (in.get(c) && !std::isspace(c) && c != ':' && c != ')') {
            read_str += c;
        }

        if (in && !std::isspace(c)) {
            in.putback(c);
        }

        if (read_str != dest.exp) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        return in >> std::scientific >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        char c1, c2, c3;
        in >> c1 >> c2 >> c3;

        if (in && c1 == '\'' && c3 == '\'') {
            dest.ref = c2;
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringLitIO&& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        return in >> std::quoted(dest.ref);
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        if (const std::istream::sentry sentry(in); !sentry) return in;

        DataStruct data;
        std::string key_label;
        bool key1_read = false, key2_read = false, key3_read = false;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};
        if (!in) return in;

        while (in.peek() != ')') {
            if (!(in >> key_label)) break;

            if (key_label == "key1") {
                if (!(in >> DoubleSciIO{data.key1} >> DelimiterIO{':'})) break;
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

            if (in.fail()) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        if (const std::ostream::sentry sentry(out); !sentry) return out;

        iofmtguard fmtguard(out);

        out << "(:";
        out << "key1 " << std::scientific << std::setprecision(1) << data.key1 << ":";
        out << "key2 " << '\'' << data.key2 << '\'' << ":";
        out << "key3 " << std::quoted(data.key3);
        out << ":)";

        return out;
    }
 }

int main() {
    using nspace::DataStruct;

    std::vector<DataStruct> data;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end());

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}