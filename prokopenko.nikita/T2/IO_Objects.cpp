#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iostream>

namespace prokopenko {

  // ???????? ????? ??? CharIO (?????????? c ?????????? ?? ??????)
  std::istream& operator>>(std::istream& in, CharIO& c) {
    char ch;
    in >> ch;
    if (ch != '\'') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> c.ref;
    in >> ch;
    if (ch != '\'') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  // ???????? ?????? ??? CharIO
  std::ostream& operator<<(std::ostream& out, const CharIO& c) {
    iofmtguard guard(out);
    return out << '\'' << c.ref << '\'';
  }

  // ???????? ????? ??? DataStruct (??????, ?????? ?? ???? ????)
  std::istream& operator>>(std::istream& in, DataStruct& ds) {
    CharIO keyIO{ ds.key };
    CharIO chIO{ ds.character };
    CharIO valueIO{ ds.value };

    if (!(in >> keyIO >> chIO >> valueIO)) {
      return in;
    }
    return in;
  }

  // ???????? ?????? ??? DataStruct
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    iofmtguard guard(out);
    return out << "("
      << CharIO{ ds.key } << " "
      << CharIO{ ds.character } << " "
      << CharIO{ ds.value } << ")";
  }

} // namespace prokopenko
