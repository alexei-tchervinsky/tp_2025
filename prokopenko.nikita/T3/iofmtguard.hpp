#pragma once
#include <iostream>
#include <iomanip>

namespace prokopenko {

  class iofmtguard {
  public:
    iofmtguard(std::ios& s)
      : s_(s), flags_(s.flags()), precision_(s.precision()) {
    }
    ~iofmtguard() {
      s_.flags(flags_);
      s_.precision(precision_);
    }

  private:
    std::ios& s_;
    std::ios::fmtflags flags_;
    std::streamsize precision_;
  };

}
