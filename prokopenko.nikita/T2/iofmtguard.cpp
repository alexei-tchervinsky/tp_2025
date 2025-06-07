#include "iofmtguard.hpp"

namespace prokopenko {

<<<<<<< HEAD
  iofmtguard::iofmtguard(std::basic_ios<char>& stream)
    : stream_(stream),
    fill_(stream.fill()),
    precision_(stream.precision()),
    flags_(stream.flags()) {
  }

  iofmtguard::~iofmtguard() {
    stream_.fill(fill_);
    stream_.precision(precision_);
    stream_.flags(flags_);
  }
=======
    iofmtguard::iofmtguard(std::basic_ios<char>& stream)
        : stream_(stream),
        fill_(stream.fill()),
        precision_(stream.precision()),
        flags_(stream.flags()) {}

    iofmtguard::~iofmtguard() {
        stream_.fill(fill_);
        stream_.precision(precision_);
        stream_.flags(flags_);
    }
>>>>>>> 5562f3d43e256a43aea295b2fa950bc06f920b4c

}

