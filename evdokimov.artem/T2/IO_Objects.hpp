#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <iostream>
#include <string>

namespace evdokimov {
struct DelimiterIO {
  char delimiter;
};

struct ComplexNumIO {
  std::complex<double> &ref;
};

struct StringIO {
  std::string &ref;
};

struct HexULongIO {
  unsigned long long &ref;
};

struct LabelIO {
  std::string label;
};

std::istream &operator>>(std::istream &, LabelIO &&);
std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, ComplexNumIO &&dest);
std::istream &operator>>(std::istream &in, HexULongIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
} // namespace evdokimov

#endif
