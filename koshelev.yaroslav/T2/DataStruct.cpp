#include "DataStruct.h"
#include "IO_Objects.h"
#include "iofmtguard.h"

#include <iomanip>
#include <cmath>

namespace solution
{
  bool DataStruct::operator<(const DataStruct& other) const
  {
    if (std::abs(key1) != std::abs(other.key1))
    {
      return std::abs(key1) < std::abs(other.key1);
    }
    if (key2 != other.key2)
    {
      return key2 < other.key2;
    }
    return key3.size() < other.key3.size();
  }

  std::istream& operator>>(std::istream& in, DataStruct& value)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }

    DataStruct temp;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> DelimiterIO{'('} >> DelimiterIO{':'};

    for (int i = 0; i < 3 && in; ++i)
    {
      std::string label;
      in >> LabelIO{label};

      if (label == "key1")
      {
        in >> ComplexIO{temp.key1} >> DelimiterIO{':'};
        hasKey1 = in.good();
      }
      else if (label == "key2")
      {
        in >> CharIO{temp.key2} >> DelimiterIO{':'};
        hasKey2 = in.good();
      }
      else if (label == "key3")
      {
        in >> StringIO{temp.key3} >> DelimiterIO{':'};
        hasKey3 = in.good();
      }
      else
      {
        std::string discard;
        std::getline(in, discard, ':');
      }
    }

    in >> DelimiterIO{')'};

    if (hasKey1 && hasKey2 && hasKey3)
    {
      value = temp;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& value)
  {
    std::ostream::sentry s(out);
    if (!s)
    {
      return out;
    }

    iofmtguard guard(out);

    out << "(:key1 #c(" << std::fixed << std::setprecision(1)
        << value.key1.real() << " " << value.key1.imag()
        << "):key2 '" << value.key2
        << "':key3 " << std::quoted(value.key3) << ":)";
    return out;
  }
}
