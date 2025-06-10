#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <string>
#include <complex>

namespace prokopenko {

  struct DelimiterIO {
    char expected;
  };

  struct LabelIO {
    std::string& ref;
  };

  struct ComplexIO {
    std::complex<double>& ref;
  };

  struct CharIO {
    char& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  struct UnsignedLongLongIO {
    unsigned long long& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& d);
  std::istream& operator>>(std::istream& in, LabelIO&& label);
  std::istream& operator>>(std::istream& in, ComplexIO&& c);
  std::istream& operator>>(std::istream& in, CharIO&& c);
  std::istream& operator>>(std::istream& in, StringIO&& s);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& v);

}

#endif
