#include "IO_Objects.hpp"

#include <iomanip>
#include <sstream>

namespace solution
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& d)
  {
    char c;
    in >> std::ws >> c;
    if (!in || c != d.expected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& l)
  {
    l.ref.clear();
    char c;
    while (in.get(c))
    {
      if (c == ' ')
      {
        break;
      }
      l.ref += c;
    }
    if (l.ref.empty())
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ComplexIO&& c)
  {
    char hash, ch, open, close;
    double real, imag;
    in >> hash >> ch >> open;
    if (hash != '#' || ch != 'c' || open != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> real >> imag >> close;
    if (!in || close != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    c.ref = std::complex<double>{real, imag};
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& c)
  {
    char quote1, ch, quote2;
    in >> quote1 >> ch >> quote2;
    if (quote1 != '\'' || quote2 != '\'')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    c.ref = ch;
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& s)
  {
    char quote;
    in >> std::ws >> quote;
    if (quote != '"')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::getline(in, s.ref, '"');
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
