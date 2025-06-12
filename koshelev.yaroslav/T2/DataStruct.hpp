#pragma once

#include <iostream>
#include <iomanip>
#include <string>

namespace solution {

    struct DoubleSciIO {
        double& ref;
    };

    struct HexUllIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DoubleSciIO&& d);
    std::istream& operator>>(std::istream& in, HexUllIO&& h);
    std::istream& operator>>(std::istream& in, StringIO&& s);

    std::ostream& operator<<(std::ostream& out, const DoubleSciIO& d);
    std::ostream& operator<<(std::ostream& out, const HexUllIO& h);
    std::ostream& operator<<(std::ostream& out, const StringIO& s);
}
