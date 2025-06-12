#include "IO_Objects.hpp"
#include <sstream>

namespace solution {

    std::istream& operator>>(std::istream& in, DoubleSciIO&& d) {
        double value;
        std::string token;
        if (!(in >> token)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::istringstream iss(token);
        iss >> std::scientific >> value;

        if (!iss || !iss.eof()) {
            in.setstate(std::ios::failbit);
            return in;
        }

        d.ref = value;
        return in;
    }

    std::istream& operator>>(std::istream& in, HexUllIO&& h) {
        in >> std::hex >> h.ref >> std::dec;
        if (!in) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& s) {
        std::string str;
        if (!(in >> std::ws) || in.get() != '"') {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::getline(in, str, '"');
        if (!in) {
            in.setstate(std::ios::failbit);
            return in;
        }

        s.ref = str;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DoubleSciIO& d) {
        std::ios::fmtflags f(out.flags());
        out << std::scientific << std::setprecision(6) << d.ref;
        out.flags(f);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const HexUllIO& h) {
        std::ios::fmtflags f(out.flags());
        out << std::uppercase << std::hex << "0x" << h.ref;
        out.flags(f);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const StringIO& s) {
        out << '"' << s.ref << '"';
        return out;
    }
}
