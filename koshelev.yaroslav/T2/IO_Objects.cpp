#include "IO_Objects.h"
#include <sstream>
#include <iomanip>
#include <cctype>

namespace solution {

  std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
    char ch;
    in >> std::ws >> ch;
    if (!in || ch != d.expected) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& l) {
    char ch;
    std::string result;
    while (in.get(ch)) {
      if (ch == ' ') break;
      result += ch;
    }
    if (in) l.ref = result;
    else in.setstate(std::ios::failbit);
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleSciIO&& d) {
    in >> std::ws;
    double value;
    in >> value;
    if (in) {
      d.ref = value;
    } else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ULLHexIO&& d) {
    std::string prefix;
    in >> prefix;
    if (prefix.size() < 3 || (prefix[0] != '0') || (prefix[1] != 'x' && prefix[1] != 'X')) {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::stringstream hexStream(prefix);
    hexStream >> std::hex >> d.ref;
    if (!hexStream) in.setstate(std::ios::failbit);
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
    return in;
  }

}
