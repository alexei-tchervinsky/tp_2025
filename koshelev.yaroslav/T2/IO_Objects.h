#ifndef IO_OBJECTS_H
#define IO_OBJECTS_H

#include <string>
#include <complex>
#include <iostream>

namespace solution
{
  struct DelimiterIO
  {
    char expected;
  };

  struct LabelIO
  {
    std::string& ref;
  };

  struct ComplexIO
  {
    std::complex<double>& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&&);
  std::istream& operator>>(std::istream& in, LabelIO&&);
  std::istream& operator>>(std::istream& in, ComplexIO&&);
  std::istream& operator>>(std::istream& in, CharIO&&);
  std::istream& operator>>(std::istream& in, StringIO&&);
}

#endif
