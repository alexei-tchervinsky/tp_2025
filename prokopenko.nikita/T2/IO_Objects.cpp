#include "IO_Objects.hpp"

#include <cctype>
#include <sstream>

namespace prokopenko {

  std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
    char ch;
    in >> std::ws >> ch;
    if (!in || ch != d.expected) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& label) {
    std::string result;
    char ch;
    while (in.get(ch)) {
      if (ch == ' ') {
        break;
      }
      result += ch;
    }
    if (in) {
      label.ref = result;
    }
    else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& c) {
    char quote1, value, quote2;
    in >> quote1 >> value >> quote2;
    if (in && quote1 == '\'' && quote2 == '\'') {
      c.ref = value;
    }
    else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ULLIO&& u) {
    unsigned long long value = 0;
    in >> value;
    if (in) {
      u.ref = value;
    }
    else {
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
