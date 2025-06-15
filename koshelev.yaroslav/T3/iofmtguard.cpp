#include "iofmtguard.h"

namespace koshelev {

    iofmtguard::iofmtguard(std::ios& stream)
        : stream_(stream),
          fillChar_(stream.fill()),
          precision_(stream.precision()),
          fmtFlags_(stream.flags()) {}

    iofmtguard::~iofmtguard() {
        stream_.fill(fillChar_);
        stream_.precision(precision_);
        stream_.flags(fmtFlags_);
    }

}

