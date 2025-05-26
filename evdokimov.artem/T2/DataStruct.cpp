#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"

#include <iomanip>

namespace evdokimov {
std::ostream &operator<<(std::ostream &os, const DataRecord &rec) {
  std::ostream::sentry sentry(os);
  if (!sentry) {
    return os;
  }
  os << "(:val1 0x";
  os << std::setbase(16) << std::uppercase << rec.val1_;
  os << ":val2 #c(";
  DataRecord::formatDouble(os, rec.val2_.real());
  os << " ";
  DataRecord::formatDouble(os, rec.val2_.imag());
  os << "):val3 \"";
  os << rec.val3_;
  os << "\":)";
  return os;
}

void DataRecord::formatDouble(std::ostream &out, double num) {
  iofmtguard outGuard(out);
  if (std::floor(num) == num) {
    out << std::fixed << std::setprecision(1) << num;
  } else {
    out << num;
  }
}

std::istream &operator>>(std::istream &in, DataRecord &rec) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataRecord temp;
  in >> DelimiterIO{'('};
  for (std::size_t i = 0; i < 3; i++) {
    short num = 0;
    in >> DelimiterIO{':'} >> LabelIO{"key"} >> num;
    switch (num) {
    case HEX: {
      in >> HexULongIO{temp.val1_};
      break;
    }
    case COMPLEX: {
      in >> ComplexNumIO{temp.val2_};
      break;
    }
    case STRING: {
      in >> StringIO{temp.val3_};
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

bool sortByCriteria(const DataRecord &a, const DataRecord &b) {
  if (a.val1_ != b.val1_) {
    return a.val1_ < b.val1_;
  }
  double absVal1 = std::abs(a.val2_);
  double absVal2 = std::abs(b.val2_);
  if (absVal1 != absVal2) {
    return absVal1 < absVal2;
  }
  return a.val3_.length() < b.val3_.length();
}
} // namespace evdokimov
