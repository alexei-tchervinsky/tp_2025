//
// Created by jdh99 on 15.04.2025.
//

#include "iofmtguard.hpp"


namespace ryzhov {
    iofmtguard::iofmtguard(std::basic_ios<char> &s):
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard() {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
