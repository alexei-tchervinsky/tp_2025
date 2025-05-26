#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"

#include <iomanip>

namespace evdokimov {
std::ostream &operator<<(std::ostream &os, const DataStruct &rec) {
  std::ostream::sentry sentry(os);
  if (!sentry) {
    return os;
  }
  os << "(:key1 0x";
  os << std::setbase(16) << std::uppercase << rec.key1_;
  os << ":key2 #c(";
  DataStruct::formatDouble(os, rec.key2_.real());
  os << " ";
  DataStruct::formatDouble(os, rec.key2_.imag());
  os << "):key3 \"";
  os << rec.key3_;
  os << "\":)";
  return os;
}

void DataStruct::formatDouble(std::ostream &out, double num) {
  iofmtguard outGuard(out);
  if (std::floor(num) == num) {
    out << std::fixed << std::setprecision(1) << num;
  } else {
    out << num;
  }
}

std::istream &operator>>(std::istream &in, DataStruct &rec) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct temp;
  in >> DelimiterIO{'('};
  for (std::size_t i = 0; i < 3; i++) {
    short num = 0;
    in >> DelimiterIO{':'} >> LabelIO{"key"} >> num;
    switch (num) {
    case HEX: {
      in >> HexULongIO{temp.key1_};
      break;
    }
    case COMPLEX: {
      in >> ComplexNumIO{temp.key2_};
      break;
    }
    case STRING: {
      in >> StringIO{temp.key3_};
      break;
    }
    }
  }
  in >> DelimiterIO{':'} >> DelimiterIO{')'};
  if (in) {
    rec = temp;
  }
  return in;
}

bool sortByCriteria(const DataStruct &a, const DataStruct &b) {
  if (a.key1_ != b.key1_) {
    return a.key1_ < b.key1_;
  }
  double absKey1 = std::abs(a.key2_);
  double absKey2 = std::abs(b.key2_);
  if (absKey1 != absKey2) {
    return absKey1 < absKey2;
  }
  return a.key3_.length() < b.key3_.length();
}
} // namespace evdokimov
