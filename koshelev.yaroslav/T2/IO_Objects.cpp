#include "IO_Objects.hpp"
#include <iomanip>
#include <sstream>

namespace solution {
  std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
    char c;
    in >> std::ws >> c;
    if (!in || c != d.expected) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& l) {
    l.ref.clear();
    char c;
    while (in.get(c)) {
      if (c == ' ') {
        break;
      }
      l.ref += c;
    }
    if (l.ref.empty()) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleIO&& d) {
    in >> d.ref;
    if (!in) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, HexUllIO&& h) {
    in >> std::hex >> h.ref;
    if (!in) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& s) {
    char quote;
    in >> std::ws >> quote;
    if (quote != '"') {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::getline(in, s.ref, '"');
    if (!in) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
