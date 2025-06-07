#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <complex>
#include <iostream>

namespace prokopenko {

  struct DelimiterIO {
    char expected;
  };

  struct LabelIO {
    std::string& ref;
  };

  struct CharIO {
    char& ref;
  };

  struct UllIO {
    unsigned long long& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&&);
  std::istream& operator>>(std::istream& in, LabelIO&&);
  std::istream& operator>>(std::istream& in, CharIO&&);
  std::istream& operator>>(std::istream& in, UllIO&&);
  std::istream& operator>>(std::istream& in, StringIO&&);

} // namespace prokopenko

#endif
