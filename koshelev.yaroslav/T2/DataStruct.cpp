#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace nspace {

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::istream::sentry sent(is);
    if (!sent) return is;
    DataStruct tmp{0.0,0ull,""};
    is >> DelimiterIO{'('};
    if (!is) return is;
    for (int i = 0; i < 3; ++i) {
        short n;
        is >> DelimiterIO{':'} >> LabelIO{"key"} >> n;
        if (!is) { is.setstate(std::ios::failbit); return is; }
        switch (n) {
            case 1: is >> DoubleSciIO{tmp.key1}; break;
            case 2: is >> ULLHexIO{tmp.key2};   break;
            case 3: is >> StringIO{tmp.key3};  break;
            default: is.setstate(std::ios::failbit); return is;
        }
        if (!is) return is;
    }
    is >> DelimiterIO{':'} >> DelimiterIO{')'};
    if (is) ds = std::move(tmp);
    return is;
}

static std::string format_sci(double v) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(1) << v;
    std::string s = oss.str();
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    auto p = s.find('e');
    if (p != std::string::npos && s.size() > p+2 && s[p+2] == '0') {
        s.erase(p+2, 1);
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    std::ostream::sentry sent(os);
    if (!sent) return os;
    iofmtguard guard(os);
    os << "(:key1 " << format_sci(ds.key1)
       << ":key2 0x" << std::hex << std::uppercase << ds.key2 << std::dec
       << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3 < b.key3;
}

}
