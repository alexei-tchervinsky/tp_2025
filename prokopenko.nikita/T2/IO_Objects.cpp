#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <ios>

namespace prokopenko {

  std::istream& operator>>(std::istream& in, CharIO&& c) {
    char quote1 = 0, quote2 = 0;
    char value;

    if (in >> quote1 >> value >> quote2) {
      if (in && quote1 == '\'' && quote2 == '\'') {
        c.ref = value;
      }
      else {
        in.setstate(std::ios::failbit);
      }
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const CharIO& c) {
    iofmtguard guard(out);
    out << '\'' << c.ref << '\'';
    return out;
  }

  std::istream& operator>>(std::istream& in, DataStruct& ds) {
    char c = 0;
    if (!(in >> c) || c != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }

    CharIO keyIO{ ds.key };
    CharIO chIO{ ds.character };
    CharIO valueIO{ ds.value };

    if (!(in >> keyIO >> chIO >> valueIO)) {
      return in;
    }

    if (!(in >> c) || c != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    iofmtguard guard(out);
    out << "("
      << CharIO{ ds.key } << " "
      << CharIO{ ds.character } << " "
      << CharIO{ ds.value } << ")";
    return out;
  }

} // namespace prokopenko
